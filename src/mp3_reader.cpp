#include "mp3_reader.hpp"

mp3_reader::mp3_reader(std::ifstream& file)
    : file(file)
{
}

bool mp3_reader::read_next_bits(int num_bits)
{
    int bits_read = 0;
    while (bits_read < num_bits)
    {
        if (bit_buffer.empty())
        {
            uint8_t byte;
            if (!file.read(reinterpret_cast<char*>(&byte), 1))
            {
                return false;
            }

            std::bitset<8> bits(byte);
            for (int i = 7; i >= 0; --i)
            {
                bit_buffer.push_back(bits[i]);
            }
        }

        std::cout << bit_buffer.front();
        bit_buffer.erase(bit_buffer.begin());
        ++bits_read;

        if (bits_read % 8 == 0)
        {
            std::cout << "\t";
        }
    }

    std::cout << std::endl;
    return true;
}
