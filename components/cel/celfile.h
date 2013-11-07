#ifndef CEL_FILE_H
#define CEL_FILE_H

#include <stdint.h>
#include <vector>
#include <map>

class Cel_frame;


struct colour
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    bool visible;

    colour(uint8_t _r, uint8_t _g, uint8_t _b, bool _visible)
    {
        r = _r; g = _g; b = _b; visible = _visible;
    }

    colour(){ visible = true; }
};

class Cel_file
{
    public:
        Cel_file(std::string filename);
        

        size_t num_frames();

        Cel_frame& operator[] (size_t index);

    private:
        size_t get_frame(size_t frame_num, std::vector<colour>& raw_image);

        size_t read_num_frames();
        void read_frame_offsets();
        
        static bool greater_than_first(const std::vector<uint8_t>& frame);
        static bool greater_than_second(const std::vector<uint8_t>& frame);
        static bool is_greater_than(const std::vector<uint8_t>& frame);
        
        void drawRow(int row, int end, int& i, const std::vector<uint8_t>& frame, colour* pal, std::vector<colour>& raw_image, bool lessThan);

        void decode_greater_less_than(const std::vector<uint8_t>& frame, colour* pal, std::vector<colour>& raw_image, bool lessThan);

        void decode_greater_than(const std::vector<uint8_t>& frame, colour* pal, std::vector<colour>& raw_image);

        bool less_than_first(const std::vector<uint8_t>& frame);
        bool less_than_second(const std::vector<uint8_t>& frame);
        bool is_less_than(const std::vector<uint8_t>& frame);

        void decode_less_than(const std::vector<uint8_t>& frame, colour* pal, std::vector<colour>& raw_image);

        void get_pal(std::string pal_filename, colour* pal);
        void fill_t(size_t pixels, std::vector<colour>& raw_image);
        int32_t normal_width(const std::vector<uint8_t>& frame, bool from_header, uint16_t offset);
        void normal_decode(const std::vector<uint8_t>& frame, size_t width, bool from_header, colour* pal, std::vector<colour>& raw_image);
        size_t decode_raw_32(const std::vector<uint8_t>& frame, colour* pal, std::vector<colour>& raw_image);
        bool ends_with(const std::string& full, const std::string& end);
        std::string replace_end(const std::string& old_end, const std::string& new_end, const std::string& original);
        bool is_tile_cel(const std::string& file_name);
        void get_pallette(std::string filename, colour* pal);

        FILE * mFile;
        
        colour* mPal;
        
        std::vector<uint32_t> mFrame_offsets;

        bool mIs_tile_cel;
        
        std::map<size_t, Cel_frame> mCache;
};

#endif