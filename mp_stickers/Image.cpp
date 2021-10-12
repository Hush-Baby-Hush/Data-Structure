#include "Image.h"

void Image::darken 	( 		) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.l -=0.1;
            if(pixel.l<0)
            {
                pixel.l = 0;
            }
        }
    }
    return;
}

void Image::darken 	(   double   amount     ) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.l -=amount;
            if(pixel.l<0)
            {
                pixel.l = 0;
            }
        }
    }
    return;
}

void Image::desaturate 	( 		) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.s -=0.1;
            if(pixel.s<0)
            {
                pixel.s = 0;
            }
        }
    }
    return;

}

void Image::desaturate 	( 	double  	amount	) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.s -=amount;
            if(pixel.s<0)
            {
                pixel.s = 0;
            }
        }
    }
    return;

}

void Image::grayscale 	( 		) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.s =0;
        }
    }
    return;
    
}

void Image::illinify 	( 		) 	
{
    for (unsigned int x = 0; x < width(); x++) 
    {
        for (unsigned int y = 0; y < height(); y++) 
        {
            cs225::HSLAPixel & pixel = getPixel(x, y);
            if(pixel.h>=((11+216)*0.5) && pixel.h <= (216+(360-216+11)*0.5))
            {
                pixel.h = 216;
            }
            else
            {
                pixel.h = 11;
            }
        }
    }
    return;
}

void Image::lighten 	( 		) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.l +=0.1;
            if(pixel.l>1)
            {
                pixel.l = 1;
            }
        }
    }
    return;
}

void Image::lighten 	( 	double  	amount	) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.l +=amount;
            if(pixel.l>1)
            {
                pixel.l = 1;
            }
        }
    }
    return;
}

void Image::rotateColor 	( 	double  	degrees	) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.h +=degrees;
            if (pixel.h < 0)
            {
                pixel.h +=360;
            }
            if(pixel.h>360)
            {
                pixel.h -= 360;
            }
        }
    }
    return;
}

void Image::saturate 	( 		) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.s +=0.1;
            if(pixel.s>1)
            {
                pixel.s = 1;
            }
        }
    }
    return;
}

void Image::saturate 	( 	double  	amount	) 	
{
    for(unsigned int i =0;i<width();i++)
    {
        for(unsigned int j =0;j<height();j++)
        {
            cs225::HSLAPixel & pixel = getPixel(i,j);
            pixel.s +=amount;
            if(pixel.s>1)
            {
                pixel.s = 1;
            }
        }
    }
    return;
}

void Image::scale 	( 	double  	factor	) 	
{
    unsigned int new_width = factor*width();
    unsigned int new_height = factor*height();

    cs225::PNG* new_image = new PNG(new_width,new_height);
    for(unsigned int i =0;i<new_width;i++)
    {
        for(unsigned int j =0;j<new_height;j++)
        {
            unsigned int w = i/factor;
            unsigned int h = j/factor;
            cs225::HSLAPixel & pixel = getPixel(w,h);
            new_image->getPixel(i,j)=pixel;
        }
    }
    resize(new_width,new_height);
    for(unsigned int i =0;i<new_width;i++)
    {
        for(unsigned int j =0;j<new_height;j++)
        {
            cs225::HSLAPixel & new_pixel = new_image->getPixel(i,j);
            getPixel(i,j)=new_pixel;
        }
    }

    delete new_image;

    return;
    

}
void Image::scale 	( 	unsigned  	w, unsigned  	h )
{
    double factor1 = (double)w/width();
    double factor2 = (double)h/height();
    double factor;
    if (factor1>=factor2)
    {
        factor = factor2;
    }
    else
    {
        factor = factor1;
    }
    scale(factor);
    return;

} 