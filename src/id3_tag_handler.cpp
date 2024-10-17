#include "id3_tag_handler.hpp"

#include <codecvt>
#include <locale>
#include <stdexcept>

id3_tag_handler::id3_tag_handler(std::ifstream& file)
{
    store_id3_tag(file);
    parse_id3_frames();
}

const std::vector<char>& id3_tag_handler::get_id3_tag() const
{
    return id3_tag;
}

bool id3_tag_handler::has_id3_tag() const
{
    return !id3_tag.empty();
}

std::string id3_tag_handler::get_metadata(const std::string& frame_id) const
{
    auto it = metadata.find(frame_id);
    if (it != metadata.end())
    {
        return it->second;
    }
    return "Not Found";
}

void id3_tag_handler::store_id3_tag(std::ifstream& file)
{
    char id3_header[10];
    if (!file.read(id3_header, 10))
    {
        return;
    }

    if (id3_header[0] == 'I' && id3_header[1] == 'D' && id3_header[2] == '3')
    {
        id3_tag.insert(id3_tag.end(), id3_header, id3_header + 10);

        unsigned int tag_size = ((id3_header[6] & 0x7F) << 21) |
                                ((id3_header[7] & 0x7F) << 14) |
                                ((id3_header[8] & 0x7F) << 7) |
                                (id3_header[9] & 0x7F);

        std::vector<char> tag_data(tag_size);
        if (!file.read(tag_data.data(), tag_size))
        {
            return;
        }

        id3_tag.insert(id3_tag.end(), tag_data.begin(), tag_data.end());
    }
    else
    {
        file.seekg(0, std::ios::beg);
    }
}

void id3_tag_handler::parse_id3_frames()
{
    size_t index = 10;

    while (index < id3_tag.size())
    {
        if (index + 10 > id3_tag.size())
        {
            break;
        }

        std::string frame_id(id3_tag.begin() + index, id3_tag.begin() + index + 4);
        index += 4;

        unsigned int frame_size = (id3_tag[index] << 24) | (id3_tag[index + 1] << 16) |
                                  (id3_tag[index + 2] << 8) | id3_tag[index + 3];
        index += 4;

        index += 2;

        if (frame_id[0] == 'T')
        {
            if (frame_size > 0)
            {
                char encoding = id3_tag[index];
                index++;

                if (encoding == 0)
                {
                    std::string content(id3_tag.begin() + index, id3_tag.begin() + index + frame_size - 1);
                    metadata[frame_id] = content;
                }
                else if (encoding == 1)
                {
                    std::u16string utf16_content(reinterpret_cast<const char16_t*>(&id3_tag[index]), (frame_size - 1) / 2);

                    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
                    std::string utf8_content = convert.to_bytes(utf16_content);
                    metadata[frame_id] = utf8_content;
                }

                index += (frame_size - 1);
            }
        }
        else
        {
            index += frame_size;
        }
    }
}
