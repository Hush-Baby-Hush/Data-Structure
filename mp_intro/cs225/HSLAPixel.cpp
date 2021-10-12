/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
    HSLAPixel::HSLAPixel ()
    {
        a = 1.0;
        l = 1.0;
        h = 0;
        s = 0;

    }

    HSLAPixel::HSLAPixel (double hue, double saturation, double luminance)
    {
        a = 1.0;
        if(hue>=0 && hue<360)
        {
            h = hue;
        }
        if(luminance>=0 && luminance<=1)
        {
            l = luminance;
        }
        if(saturation>=0 && saturation<=1)
        {
            s = saturation;
        }


    }

    HSLAPixel::HSLAPixel (double hue, double saturation, double luminance, double alpha)
    {
        if(alpha>=0 && alpha<=1)
        {
            a = alpha;
        }

        if(hue>=0 && hue<360)
        {
            h = hue;
        }

        if(saturation>=0 && saturation<=1)
        {
            s = saturation;
        }
        
        if(luminance>=0 && luminance<=1)
        {
            l = luminance;
        }

        

    }
}