/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"


class Stickers
{

    public:
        Stickers(/* args */);
        Stickers(Image & sticker, unsigned x, unsigned y);
        ~Stickers();
        Image* sticker_;
        unsigned x_;
        unsigned y_;

};


class StickerSheet
{
    private:
        Stickers** array;
        Image* base_pic;
        unsigned max_;
        unsigned current_;
        void    clear(  );
        void    copy(const StickerSheet & other);
        
    public:
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet ();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & 	operator= (const StickerSheet &other);
        void 	changeMaxStickers (unsigned max);
        int 	addSticker (Image &sticker, unsigned x, unsigned y);
        bool 	translate (unsigned index, unsigned x, unsigned y);
        void 	removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image 	render () const;
};


