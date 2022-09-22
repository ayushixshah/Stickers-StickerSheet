#include "StickerSheet.h"


StickerSheet::StickerSheet (const Image &picture, unsigned max){
    ima = new Image(picture);  
    max_stick = max; 
    for(int i = 0; i < (int)(this->stickers.size()); i++){
        this->stickers.pop_back();
        this->x_coordinates.pop_back();
        this->y_coordinates.pop_back();
    }
}
StickerSheet::~StickerSheet(){
    for(int i = 0; i < int(this->stickers.size()); i++){
        this->stickers.pop_back();
        this->x_coordinates.pop_back();
        this->y_coordinates.pop_back();
    }
    delete ima; 
}
StickerSheet::StickerSheet(const StickerSheet &other){
    this->ima = new Image(*other.ima); 
    this->max_stick = other.max_stick;
    int i = 0; 
    // other.~StickerSheet();
        while (i < (int)other.stickers.size()) {
            this->x_coordinates.push_back((other.x_coordinates.at(i)));
            this->y_coordinates.push_back(other.y_coordinates.at(i));
            this->stickers.push_back(other.stickers.at(i));
            i++;
        }
}
void StickerSheet::CreatPixel(cs225::HSLAPixel pixel_one, cs225::HSLAPixel pixel_two) const {
    pixel_one.h = pixel_two.h;
    pixel_one.s = pixel_two.s;
    pixel_one.l = pixel_two.l;
    pixel_one.a = pixel_two.a;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    this->ima = new Image(*other.ima); 
    this->max_stick = other.max_stick;
    int i = 0; 
        while (i < (int)other.stickers.size()) {
            this->x_coordinates.push_back(other.x_coordinates.at(i));
            this->y_coordinates.push_back(other.y_coordinates.at(i));
            this->stickers.push_back(other.stickers.at(i));
            i++;
        }
    return *this; 
} 
void StickerSheet::changeMaxStickers (unsigned max){
    if (max_stick > (int)max) {
        for (int i = max_stick; i < (int)max; i++) {
            stickers.pop_back();
            x_coordinates.pop_back();
            y_coordinates.pop_back();
        }
    }
    max_stick = max;
}
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    bool max_reached = false; 
    if ((int)stickers.size() == max_stick) {
        max_reached = true;
    }
    if (!max_reached) {
        stickers.push_back(&sticker);
        x_coordinates.push_back(x);
        y_coordinates.push_back(y);
       // std::cout << "sticker added. stickers size: " << stickers.size() << std::endl;
    }
    
    return stickers.size() - 1; 
// adding a sticker to the stickersheet
//include the x and y coordinates to the vectors 
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    if (index < 0 || index >= stickers.size()) {
        return false; 
    } 
    if (index >=0 && index < stickers.size()) {
    x_coordinates.at(index) = x; 
    y_coordinates.at(index) = y; 
    return true; 
    }
    return true; 
}
void StickerSheet::removeSticker (unsigned index){
    if (index < stickers.size() && index >= 0) {
        stickers.erase(stickers.begin() + index); 
        x_coordinates.erase(x_coordinates.begin() + index);
        y_coordinates.erase(y_coordinates.begin() + index);
    }
}
Image* StickerSheet::getSticker (unsigned index){
    if (index > stickers.size() || index < 0) {
        return nullptr;
    }
    if (index >= 0 && index < stickers.size()) {
        return stickers.at(index);
    }
    return nullptr; 
}
Image StickerSheet::render() const {
    Image return_image(*ima);
    // first find the max height ad width of the image
    unsigned width_final = return_image.width();
    unsigned height_final = return_image.height();
    uint i = 0; 
    while (i < this->stickers.size()) {
     
    // create the return object by using private variable 
    //for (int i = 0; i < (int)this->stickers.size(); i++) {
        std::cout << "inside for loop in render" << std::endl;
        uint temp_w = this->stickers.at(i)->width(); uint temp_h = this->stickers.at(i)->height();
        uint curr_w = x_coordinates.at(i); uint curr_h = y_coordinates.at(i); 
        
        uint new_height = temp_h + curr_h;
        uint new_width = temp_w + curr_w;
        if (new_height > height_final) {
            height_final = new_height;
        }
        if (new_width > width_final) {
            width_final = new_width;
        }
        //i++;
    
        if (width_final > return_image.width()) {
            return_image.resize(width_final, return_image.height());
        }
        if (height_final > return_image.height()) {
            return_image.resize(return_image.width(), height_final);
        }
    
       //  std::cout << "rendering sticker " << i << " at (" << x_coordinates.at(i) << ", " << y_coordinates.at(i) << ")" << std::endl;
        // std::cout << stickers.at(i)->width() << std::endl;
        int current_width = x_coordinates.at(i);
        int current_height = y_coordinates.at(i);
        uint x = 0;
        uint y = 0; 
        while (x < this->stickers.at(i)->width()) {
            while (y < this->stickers.at(i)->height()) {
                cs225::HSLAPixel pixel_one = stickers.at(i)->getPixel(x, y); 
                cs225::HSLAPixel& pixel_two = return_image.getPixel(x + current_width, y + current_height);
                if (pixel_one.a != 0) {
                    // CreatPixel(pixel_two, pixel_one);
                    pixel_two = pixel_one;
                }
                y++; 
            }
            x++; 
        }
        i++; 
    }
    // std::cout << "render successful" << std::endl;
    return return_image;
}

