/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <iostream>
#include <vector>
#include "Image.h"

class StickerSheet {
    public: 
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet (const StickerSheet &other);
        const StickerSheet& operator=(const StickerSheet &other); 
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image render() const;
        void CreatPixel(cs225::HSLAPixel pixel_one, cs225::HSLAPixel pixel_two) const; 

    private: 
        int max_stick; 
        Image* ima;
        std::vector<Image*> stickers; 
        std::vector<int> x_coordinates; 
        std::vector<int> y_coordinates; 
};