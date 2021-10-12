/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel{
        public:
        double l;
        double a;
        double h;
        double s;

        HSLAPixel ();
        HSLAPixel (double hue, double saturation, double luminance);
        HSLAPixel (double hue, double saturation, double luminance, double alpha);

    };
}