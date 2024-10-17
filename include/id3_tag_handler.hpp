#ifndef ID3_TAG_HANDLER_HPP
#define ID3_TAG_HANDLER_HPP

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class id3_tag_handler
{
   public:
    // Constructor reads and stores the ID3 tag if present
    id3_tag_handler(std::ifstream& file);

    // Function to get the stored ID3 tag for external use
    const std::vector<char>& get_id3_tag() const;

    // Function to check if an ID3 tag was found
    bool has_id3_tag() const;

    // Retrieve specific metadata (e.g., title, artist, etc.)
    std::string get_metadata(const std::string& frame_id) const;

   private:
    std::vector<char> id3_tag;                              // Store the ID3v2 tag (header + data)
    std::unordered_map<std::string, std::string> metadata;  // Store extracted metadata

    // Function to store ID3v2 tag if present
    void store_id3_tag(std::ifstream& file);

    // Function to parse ID3v2 frames and extract metadata
    void parse_id3_frames();
};

#endif  // ID3_TAG_HANDLER_H