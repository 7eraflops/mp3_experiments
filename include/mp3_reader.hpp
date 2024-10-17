#ifndef MP3_READER_HPP
#define MP3_READER_HPP

#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

class mp3_reader
{
   public:
    mp3_reader(std::ifstream& file);

    // Read next 32 bits from the file and display them
    bool read_next_bits(int num_bits);

   private:
    std::ifstream& file;          // File reference
    std::vector<int> bit_buffer;  // Store bits from the current byte
};

#endif  // MP3_READER_H