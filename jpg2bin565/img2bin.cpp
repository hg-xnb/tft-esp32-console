#include <bits/stdc++.h>
using namespace std;
#include <jpeglib.h>

#include <cstdint> 


class IMG_SHAPE{
private:
    uint16_t width;
    uint16_t height;

public:

    IMG_SHAPE(const IMG_SHAPE& other) = default;

    IMG_SHAPE(uint16_t width = 0, uint16_t height = 0){
        this->height = height;
        this->width  = width;
    }
    
    uint16_t W() const {return this->width;}
    uint16_t H() const {return this->height;}

    IMG_SHAPE& operator = (IMG_SHAPE o){
        this->width  = o.width;
        this->height = o.height;
        return *this;
    }
    
    void set(uint16_t height, uint16_t width){
        this->height = height;
        this->width  = width;
    }

    void H(uint16_t height){this->height = height;}
    void W(uint16_t width){this->width = width;}

    bool operator == (IMG_SHAPE o){
        return (this->height == o.height)
                && (this->width == o.width);
    }
    bool operator != (IMG_SHAPE o){
        return (this->height != o.height)
                || (this->width != o.width);
    }

    uint32_t HxW() const {return uint32_t(this->height) * uint32_t(this->width);}

    friend std::ostream& operator<<(std::ostream& os, const IMG_SHAPE& o){
        os << "(" << o.height << ", " << o.width << ")";
        return os;
    }

};

class RGB_PIXEL {
private:
    uint16_t red, green, blue;

    // Convert RGB888 to RGB565
    inline uint16_t RGB_to_RGB565(uint8_t red, uint8_t green, uint8_t blue) const {
        return ((red & 0xF8) << 8) |   // Take the top 5 bits of Red
               ((green & 0xFC) << 3) | // Take the top 6 bits of Green
               ((blue & 0xF8) >> 3);   // Take the top 5 bits of Blue
    }

    // Normalize values to 8-bit range
    template <class T>
    T norm_1608(T in) const {
        return (in > 255) ? 255 : in;
    }

public:

    RGB_PIXEL(const RGB_PIXEL& other) = default;

    // Constructor
    RGB_PIXEL(uint16_t red = 0, uint16_t green = 0, uint16_t blue = 0)
        : red(red), green(green), blue(blue) {}

    // Setters
    void RED(uint16_t new_val){this->red = new_val;}
    void GREEN(uint16_t new_val){this->green = new_val;}
    void BLUE(uint16_t new_val){this->blue = new_val;}

    // Getters
    uint16_t RED() const { return red; }
    uint16_t GREEN() const { return green; }
    uint16_t BLUE() const { return blue; }

    // Assignment operator
    RGB_PIXEL& operator=(const RGB_PIXEL& o) {
        if (this != &o) {
            red = o.RED();
            green = o.GREEN();
            blue = o.BLUE();
        }
        return *this;
    }

    // Addition operators
    RGB_PIXEL operator+(const RGB_PIXEL& o) const {
        return RGB_PIXEL(RED() + o.RED(), GREEN() + o.GREEN(), BLUE() + o.BLUE());
    }

    // Self-addition
    RGB_PIXEL& operator += (const RGB_PIXEL& o) {
        this->red   = (this->red   + o.red   > 65535U) ? 65535 : this->red   + o.red;
        this->green = (this->green + o.green > 65535U) ? 65535 : this->green + o.green;
        this->blue  = (this->blue  + o.blue  > 65535U) ? 65535 : this->blue  + o.blue;
        return *this;
    }

    // Convert to 16-bit RGB565 format
    uint16_t to_565_format() const {
        return RGB_to_RGB565(
            static_cast<uint8_t>(norm_1608(RED())),
            static_cast<uint8_t>(norm_1608(GREEN())),
            static_cast<uint8_t>(norm_1608(BLUE()))
        );
    }

    bool operator == (const RGB_PIXEL& o){
        return (RED() == o.RED()) 
                && (GREEN() == o.GREEN()) 
                && (BLUE()  == o.BLUE());
    }

    bool operator != (const RGB_PIXEL& o){
        return (RED() != o.RED()) 
                || (GREEN() != o.GREEN()) 
                || (BLUE()  != o.BLUE());
    }


    friend std::ostream& operator<<(std::ostream& os, const RGB_PIXEL& pixel){
        os << "(" << pixel.RED() << ", " << pixel.GREEN() << ", " << pixel.BLUE() << ")";
        return os;
    }

};

class RGB_IMG{
private:
    uint32_t id;
    RGB_PIXEL* pixels;
    IMG_SHAPE shape;
protected:
    uint32_t xy_to_index(uint16_t x, uint16_t y,IMG_SHAPE shape) const {
        if( x >= shape.H() || y >= shape.W() ) return 0U;
        return uint32_t(x) * uint32_t(shape.W()) + uint32_t(y);
    }

    template<class Tmsg>
    void actually_print_log(Tmsg msg) const {
        // will be called at last of param list :v 
        cout << msg << '\n';
    }

    template<class Tmsg, class... Tmsgs>
    void actually_print_log(Tmsg msg, Tmsgs... msgs) const {
        cout << msg;
        actually_print_log(msgs...);
    }

    template<class... Tmsgs>
    void write_log(Tmsgs... msgs) const {
        cout << "<RGB_IMG id=" << id << "> ";
        actually_print_log(msgs...);
    }


public:
    RGB_IMG(uint16_t max_height = 0, uint16_t max_width = 0, RGB_PIXEL preset = {0, 0, 0})
    {

        this->id = uintptr_t(&id);
        if( !max_height  || !max_width ){
            this->pixels        = NULL;
            this->shape.set(0, 0);
            return;
        }else{
            this->pixels        = new RGB_PIXEL[ uint32_t(max_height) * uint32_t(max_width) ];
            this->shape.set(max_height, max_width);
        }
        if( preset != RGB_PIXEL({0, 0, 0}) ){
            for(uint32_t i = 0; i < max_height*max_width; ++i){
                *(pixels + i) = preset;
            }
        }
        write_log("initialized ", "h= ", max_height, " w= ", max_width);
    }

    RGB_IMG(string jpg_path){
        FILE* infile = fopen(jpg_path.c_str(), "rb");

        if (!infile) {
            write_log("failed to initialize!");
            exit(1);
        }

        // Decompress the JPEG file
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, infile);
        jpeg_read_header(&cinfo, TRUE);
        jpeg_start_decompress(&cinfo);

        // Get image dimensions
        this->shape.set(cinfo.output_height, cinfo.output_width);
        this->pixels    = new RGB_PIXEL[ this->shape.HxW() ];
        int channels = cinfo.output_components; // 3 for RGB

        // Allocate memory for a row of pixels
        unsigned char* row_buffer = new unsigned char[this->shape.W() * channels];

        // Read each row
        for (int x = 0; x < this->shape.H(); ++x) {
            jpeg_read_scanlines(&cinfo, &row_buffer, 1);
            for (int y = 0; y < this->shape.W(); ++y) {
                int index = y * channels;
                unsigned char red = row_buffer[index];
                unsigned char green = row_buffer[index + 1];
                unsigned char blue = row_buffer[index + 2];
                this->pixels[xy_to_index(x, y, shape)]
                = {red, green, blue};
            }
        }

        write_log("initialized", " h=", shape.H() ," w=", shape.W(), " c=", channels);

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
    }

    uint32_t ID() const {return this->id;}

    void RESIZE(uint16_t new_height, uint16_t new_width){
        delete[] pixels;
        pixels = NULL;
        this->shape.set(new_height, new_width);
        if( shape.HxW() > 0U ){
            pixels = new RGB_PIXEL[ shape.HxW() ];
        }
    }

    void SET_HEIGHT(uint16_t new_height){this->shape.H(new_height);}
    void SET_WIDTH(uint16_t new_width){this->shape.W(new_width);}
    void SET_PIXEL(uint32_t index, RGB_PIXEL new_pixel){
        if(index >= uint32_t(this->HEIGHT()) * uint32_t(this->WIDTH())){
            write_log("ERROR: ", "RGB_PIXEL.PIXEL: out-of-range");
            exit(1);
        }
        *(this->pixels + index) = new_pixel;
    }
    void SET_PIXEL(uint16_t x, uint16_t y, RGB_PIXEL new_pixel){
        if(x >= this->HEIGHT() || y >= this->WIDTH()){
            write_log("ERROR: ", "RGB_PIXEL.PIXEL: out-of-range");
            exit(1);
        }
        *(pixels + uint32_t(x) * uint32_t(this->WIDTH()) + uint32_t(y)) = new_pixel;
    }

    uint16_t HEIGHT()const {return this->shape.H();}
    uint16_t WIDTH() const {return this->shape.W();}
    IMG_SHAPE SHAPE() const {return this->shape;}

    RGB_PIXEL& PIXEL(uint32_t index) const {
        if(index >= uint32_t(this->HEIGHT()) * uint32_t(this->WIDTH())){
            this->write_log("ERROR: ", "RGB_PIXEL.PIXEL: out-of-range");
            exit(1);
        }
        return *( pixels + index);    
    }

    RGB_PIXEL& PIXEL(uint16_t x, uint16_t y) const {
        if(x >= this->HEIGHT() || y >= this->WIDTH()){
            write_log("ERROR: ", "RGB_PIXEL.PIXEL: out-of-range");
            exit(1);
        }
        return *(pixels + uint32_t(x) * uint32_t(this->WIDTH()) + uint32_t(y));
    }

    friend std::ostream& operator<<(std::ostream& os, const RGB_IMG& img){
        os << "<RGB_IMG id=" << img.ID() << ">\n";
        for(uint16_t x = 0; x < img.HEIGHT(); ++x){
            for(uint16_t y = 0; y < img.WIDTH(); ++y){
                os << img.PIXEL(x, y) << '\t';
            }
            os << '\n';
        }
        return os;
    }

    RGB_IMG& operator = (RGB_IMG const& o){
        this->RESIZE(o.HEIGHT(), o.WIDTH());
        for(uint32_t i = 0; i < uint32_t(o.HEIGHT()) * uint32_t(o.WIDTH()); ++i){
            this->SET_PIXEL(i, o.PIXEL(i));
        }
        return *this;
    }

    RGB_IMG& size_reducing(uint16_t percent) {
        if (percent == 0 || percent >= 100) {
            write_log("size_reducing::ERROR - Invalid percentage: ", percent);
            return *this;
        }

        uint16_t new_height = HEIGHT() * percent / 100;
        uint16_t new_width = WIDTH() * percent / 100;

        if (new_height == 0 || new_width == 0) {
            write_log("size_reducing::ERROR - New dimensions too small: ", new_height, "x", new_width);
            return *this;
        }

        // Allocate new buffer
        RGB_PIXEL* new_pixels = new RGB_PIXEL[new_height * new_width];

        double x_ratio = static_cast<double>(WIDTH()) / new_width;
        double y_ratio = static_cast<double>(HEIGHT()) / new_height;

        for (uint16_t new_x = 0; new_x < new_height; ++new_x) {
            for (uint16_t new_y = 0; new_y < new_width; ++new_y) {
                // Compute source coordinates in the original image
                double src_x = new_x * y_ratio;
                double src_y = new_y * x_ratio;

                uint16_t x1 = static_cast<uint16_t>(src_x);
                uint16_t y1 = static_cast<uint16_t>(src_y);
                uint16_t x2 = std::min(x1 + 1, HEIGHT() - 1);
                uint16_t y2 = std::min(y1 + 1, WIDTH() - 1);

                double x_diff = src_x - x1;
                double y_diff = src_y - y1;

                // Bilinear interpolation
                RGB_PIXEL p1 = PIXEL(x1, y1);
                RGB_PIXEL p2 = PIXEL(x1, y2);
                RGB_PIXEL p3 = PIXEL(x2, y1);
                RGB_PIXEL p4 = PIXEL(x2, y2);

                RGB_PIXEL interp;
                interp.RED(static_cast<uint16_t>(
                    p1.RED() * (1 - x_diff) * (1 - y_diff) +
                    p2.RED() * y_diff * (1 - x_diff) +
                    p3.RED() * x_diff * (1 - y_diff) +
                    p4.RED() * x_diff * y_diff
                ));
                interp.GREEN(static_cast<uint16_t>(
                    p1.GREEN() * (1 - x_diff) * (1 - y_diff) +
                    p2.GREEN() * y_diff * (1 - x_diff) +
                    p3.GREEN() * x_diff * (1 - y_diff) +
                    p4.GREEN() * x_diff * y_diff
                ));
                interp.BLUE(static_cast<uint16_t>(
                    p1.BLUE() * (1 - x_diff) * (1 - y_diff) +
                    p2.BLUE() * y_diff * (1 - x_diff) +
                    p3.BLUE() * x_diff * (1 - y_diff) +
                    p4.BLUE() * x_diff * y_diff
                ));

                new_pixels[new_x * new_width + new_y] = interp;
            }
        }

        // Replace old buffer
        delete[] pixels;
        pixels = new_pixels;
        shape.set(new_height, new_width);

        write_log("size_reducing::SUCCESS - New size: ", new_height, "x", new_width);
        return *this;
    }

    RGB_IMG& crop(uint16_t crop_h, uint16_t crop_w) {
        if (crop_h == 0 || crop_w == 0 || crop_h > HEIGHT() || crop_w > WIDTH()) {
            write_log("crop::ERROR - Invalid crop size: ", crop_h, "x", crop_w);
            return *this;
        }

        // Calculate the top-left corner of the crop area
        uint16_t start_x = (HEIGHT() - crop_h) / 2;
        uint16_t start_y = (WIDTH() - crop_w) / 2;

        // Allocate memory for cropped pixels
        RGB_PIXEL* new_pixels = new RGB_PIXEL[crop_h * crop_w];

        // Copy pixels from original image
        for (uint16_t x = 0; x < crop_h; ++x) {
            for (uint16_t y = 0; y < crop_w; ++y) {
                new_pixels[x * crop_w + y] = PIXEL(start_x + x, start_y + y);
            }
        }

        // Replace old pixel buffer
        delete[] pixels;
        pixels = new_pixels;
        shape.set(crop_h, crop_w);

        write_log("crop::SUCCESS - New size: ", crop_h, "x", crop_w);
        return *this;
    }

    bool save_to_jpg(const string& filename, int quality = 75) {
        FILE* outfile = fopen(filename.c_str(), "wb");
        if (!outfile) {
            write_log("Failed to open file for writing: ", filename);
            return false;
        }

        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr jerr;

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_compress(&cinfo);
        jpeg_stdio_dest(&cinfo, outfile);

        cinfo.image_width = WIDTH();
        cinfo.image_height = HEIGHT();
        cinfo.input_components = 3; // RGB
        cinfo.in_color_space = JCS_RGB;

        jpeg_set_defaults(&cinfo);
        jpeg_set_quality(&cinfo, quality, TRUE);
        jpeg_start_compress(&cinfo, TRUE);

        JSAMPROW row_pointer[1];
        unsigned char* row_buffer = new unsigned char[WIDTH() * 3];

        while (cinfo.next_scanline < cinfo.image_height) {
            for (int y = 0; y < WIDTH(); ++y) {
                RGB_PIXEL pixel = PIXEL(cinfo.next_scanline, y);
                row_buffer[y * 3] = static_cast<uint8_t>(pixel.RED());
                row_buffer[y * 3 + 1] = static_cast<uint8_t>(pixel.GREEN());
                row_buffer[y * 3 + 2] = static_cast<uint8_t>(pixel.BLUE());
            }
            row_pointer[0] = row_buffer;
            jpeg_write_scanlines(&cinfo, row_pointer, 1);
        }

        jpeg_finish_compress(&cinfo);
        jpeg_destroy_compress(&cinfo);
        fclose(outfile);
        delete[] row_buffer;

        write_log("Image saved to: ", filename);
        return true;
    }

    bool save_to_bin(const string& filename) {
        std::ofstream fs(filename, std::ios::out | std::ios::binary | std::ios::trunc);
        
        if (!fs) {
            write_log("ERROR: Unable to open file for writing: ", filename);
            return false;
        }

        for (uint32_t i = 0; i < shape.HxW(); ++i) {
            uint16_t _565_pixel = pixels[i].to_565_format();
            char byte_h = (_565_pixel >> 8) & 0xFF;
            char byte_l = _565_pixel & 0xFF;
            
            fs.write(&byte_h, 1);
            fs.write(&byte_l, 1);
        }

        fs.close();
        write_log("Image saved to binary file: ", filename);
        return true;
    }

    ~RGB_IMG(){
        write_log("delete[] pixels=", pixels);
        if(pixels == NULL) return;
        delete[] pixels;
        pixels = NULL;
        write_log("done!");
    }
};

string filename_extension(string filepath, bool sel = 0){
    
    /// sel  = 0 : return filename
    /// sel  = 1 : return extension

    string filename = "";
    string extension = "";

    bool got_extension = false;

    if(filepath.back() == '/' || filepath.back() == '\\') 
        filepath.pop_back();

    while(!filepath.empty()){

        if(filepath.back() == '/' || filepath.back() == '\\')
                break;

        if(filepath.back() == '.'){
            if(got_extension){
                filename.push_back(filepath.back());
                filepath.pop_back();
                continue;
            }else{
                got_extension = true;
                filepath.pop_back();
                continue;
            }
        }

        if(got_extension){
            filename.push_back(filepath.back());
        }else{
            extension.push_back(filepath.back());
        }

        filepath.pop_back();
    }

    sel?
    reverse(extension.begin(), extension.end()):
    reverse(filename.begin(), filename.end());

    return sel?extension:filename;

}

int main(int argc, char* argv[]){
    
    for(int i = 1; i < argc; i++){
        cout << "\nProcessing " << "arg[" << i << "] : " << argv[i] << '\n';

        RGB_IMG img0(argv[i]);

        if( img0.SHAPE().W() < 172 || img0.SHAPE().H() < 220 ){
            continue;
        }

        uint16_t percent = max(
            100.0 * 192 / img0.SHAPE().W(),
            100.0 * 240 / img0.SHAPE().H()
        );

        img0.size_reducing(percent);
        img0.crop(220, 172);

        string jpg_output = "./resized_imgs/" + filename_extension(argv[i]) + ".jpg";
        string bin_output = "./bins/" + filename_extension(argv[i]) + ".bin";

        img0.save_to_jpg(jpg_output.c_str(), 100);
        img0.save_to_bin(bin_output);
    }

    cout << "\n>>>> done >>>>\n";
    
    return 0;
}