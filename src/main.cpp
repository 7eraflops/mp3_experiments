#include <bitset>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/id3_tag_handler.hpp"
#include "../include/mp3_reader.hpp"

int main()
{
    try
    {
        std::ifstream file("../spotifydown.com - For Whom The Bell Tolls - Remastered.mp3", std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file.");
        }

        // Handle ID3 tag
        id3_tag_handler id3_handler(file);

        // Display metadata if ID3 tag is found
        if (id3_handler.has_id3_tag())
        {
            std::cout << "Title: " << id3_handler.get_metadata("TIT2") << std::endl;
            std::cout << "Artist: " << id3_handler.get_metadata("TPE1") << std::endl;
            std::cout << "Album: " << id3_handler.get_metadata("TALB") << std::endl;
            std::cout << "Year: " << id3_handler.get_metadata("TYER") << std::endl;
        }
        else
        {
            std::cout << "No ID3 tag found." << std::endl;
        }

        // Continue reading MP3 frames if needed
        mp3_reader reader(file);
        const int bits_per_read = 32;  // Display 32 bits at a time
        char user_input;

        // Keep reading bits as long as the user presses a key
        while (true)
        {
            std::cout << "Press Enter to read the next 32 bits, or 'q' to quit: ";
            std::cin.get(user_input);

            if (user_input == 'q')
            {
                break;
            }

            if (!reader.read_next_bits(bits_per_read))
            {
                std::cout << "End of file reached." << std::endl;
                break;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
