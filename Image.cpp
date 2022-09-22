#include "Image.h"
#include <iostream> 
#include <cmath>

void Image::lighten() {
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
            if(pixel.l > .9) {
                pixel.l = 1; 
            } else if (pixel.l > 0 && pixel.l <= .9) {
                pixel.l += .1; 
            }
        }
    }
}
void Image::lighten(double amo){
    // Image* image = new Image[]
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
                if(pixel.l > 1 - amo) {
                    pixel.l = 1; 
                }else {
            // } else if (pixel.l > 0 && pixel.l <= 1 - amo) {
                pixel.l += amo; 
            }
        }
    }

}
void Image::darken() {
    // Image* image = new Image[]
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
                if(pixel.l < .1) {
                    pixel.l = 0; 
            } else if (pixel.l > 0 && pixel.l <= 1) {
                pixel.l -= .1; 
            }
        }
    }

}
void Image::darken(double amo) {
    // Image* image = new Image[]
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
            if(pixel.l < amo) {
                pixel.l = 0; 
            } else {
                pixel.l -= amo; 
            }
        }
    }

}
void Image::saturate() {
    // Image* image = new Image[]
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
                if(pixel.s >= .9) {
                    pixel.s = 1; 
            } else if (pixel.s > 0 && pixel.s <= .9) {
                pixel.s += .1; 
            }
        }
    }

}
void Image::saturate(double amo) {
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
                if(pixel.s >= 1 - amo) {
                    pixel.s = 1; 
            } else if (pixel.s > 0 && pixel.s <= 1 - amo) {
                pixel.s += amo; 
            }
        }
    }
}
void Image::desaturate(double amo) {
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
                if(pixel.s <= amo) {
                    pixel.s = 0; 
            } else if (pixel.s > 0 && pixel.s <= 1) {
                pixel.s -= amo; 
            }
        }
    }

}
void Image::desaturate() {
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
                if(pixel.s <= .1) {
                    pixel.s = 0; 
            } else if (pixel.s > .1 && pixel.s <= 1) {
                pixel.s -= .1; 
            }
        }
    }

}
//chnage sat to 0
void Image::grayscale(){
    // Image* image = new Image[]
    unsigned width = this->width();
    unsigned  hei = this->height();
    for (uint i = 0; i < width; i++) {
        for (uint j = 0; j < hei; j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
            pixel.s = 0; 
        }
    }
}
//sets hue to oraneg or blue cuase illini!
// ornge = 30, blue = 180, middle = 105, 105 - 285 = blue and 285-360 && 0 - 30 equals orange
void Image::illinify(){
    for (uint i = 0; i < this->width(); i++) {
        for (uint j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
            if (pixel.h <= 30 && pixel.h >= 0) {
                pixel.h = 30; 
            } else if (pixel.h <= 360 && pixel.h >= 285){
                pixel.h = 30; 
            } else {
                pixel.h = 180; 
            }
        }
    }

}
void Image::rotateColor(double deg){
    for (uint i = 0; i < this->width(); i++) {
        for (uint j =0; j < this->height(); j++) {
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
            if (deg >= 0) {
                if (pixel.h + deg > 360) {
                    pixel.h =  deg - (360 - (pixel.h));
                } else {
                    pixel.h += deg;
                }
            } else {
                if (pixel.h - deg < 0) {
                    pixel.h = pixel.h + 360 + deg;
                } else {
                    pixel.h -= deg;
                }
            }        
        }
    }
}
void Image::scale(double fac){
    PNG * png_temporary = new PNG((this->width()*fac), (this->height() * fac));
    // int i = 0; 
    // int j = 0; 
    // while (i < (this->width()*fac)) {
    for (int i = 0; i < this->width() * fac; i++) {
        // while (j < (this->height() * fac)) {
        for (int j = 0; j < this->height() * fac; j++) {
            cs225::HSLAPixel & pixel_one = png_temporary->getPixel(i,j);
            cs225::HSLAPixel & pixel_two = this->getPixel(i/fac,j/fac);
            pixel_one.l = pixel_two.l;
            pixel_one.s = pixel_two.s;
            pixel_one.h = pixel_two.h;
            pixel_one.a = pixel_two.a;
            // j++;
        }
        // i++; 
    }
    this->resize((this->width()*fac), (this->height() * fac));

    for (int a = 0; a < (int)this->width(); a++) {
        for (int b = 0; b < (int)this->height(); b++) {
            cs225::HSLAPixel & pixel_two = png_temporary->getPixel(a, b);
            cs225::HSLAPixel & pixel_one = this->getPixel(a, b);
            pixel_one.l = pixel_two.l;
            pixel_one.s = pixel_two.s;
            pixel_one.h = pixel_two.h;
            pixel_one.a = pixel_two.a;
        }
    }
    delete png_temporary;
}
void Image::scale(unsigned w, unsigned h){
    double height = this->height();
    double height_another = (double)(h) / height;
    double width = this->width();
    double width_another = double(w) / width; 
    if (width_another < height_another) {
        scale(width_another);
    }
    if (width_another >= height_another) {
        scale(height_another);
    }
}