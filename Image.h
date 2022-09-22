/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"



class Image : public cs225::PNG {
    public:
        void lighten();
        void lighten(double amo);
        void darken();
        void darken(double amo);
        void saturate();
        void saturate(double amo);
        void desaturate();
        void desaturate(double amo);
        void grayscale();
        void rotateColor(double deg);
        void illinify();
        void scale(double fac);
        void scale(unsigned w, unsigned h);

};