#include "Image.h"
#include "StickerSheet.h"


void StickerSheet::copy(    const StickerSheet &  	other   )
{
    base_pic = new Image(*other.base_pic);
    max_ = other.max_;
    current_ = other.current_;
    array = new Stickers*[max_];
    for(unsigned i = 0; i<current_; i++) 
    {
        if (other.array[i]->sticker_ == nullptr)
        {
            array[i] = new Stickers();
            continue;
        }
        
        array[i] = new Stickers(*(other.array[i]->sticker_),other.array[i]->x_,other.array[i]->y_); 
    }
    return;

}


void StickerSheet::clear()
{
    if (current_==0)
    {
        if (base_pic)
        {
            delete base_pic;   
            base_pic = nullptr;
        }
        delete []array;
        array = nullptr;
        max_ = 0;
        return;
    }

    for(unsigned i = 0; i<current_; i++)
    {
        if (array[i]->sticker_!=nullptr)
        {
            delete array[i]->sticker_;
            array[i]->sticker_ = nullptr;
        }
        delete array[i];      
    }

    delete []array;
    max_ = 0;
    current_ = 0;
    
    if (base_pic)
    {
        delete base_pic;   
    }

    base_pic = nullptr;

    
    return;
}


Image * StickerSheet::getSticker 	( 	unsigned  	index	) 	
{
    if (index>current_-1)
    {
        return NULL;
    }
    
    return array[index]->sticker_;
}


Image StickerSheet::render 	( 		) 	const
{ 
    unsigned int max_width = base_pic->width();
    unsigned int max_height = base_pic->height();
    Image output;
    output.resize(max_width,max_height);
    for (unsigned i = 0; i < current_; i++)
    {
        if (array[i]->sticker_ == nullptr)
        {
            continue;
        }
        if (array[i]->x_+array[i]->sticker_->width()>max_width)
        {
            max_width = array[i]->x_+array[i]->sticker_->width();
        }
        if (array[i]->y_+array[i]->sticker_->height()>max_height)
        {
            max_height = array[i]->y_+array[i]->sticker_->height();
        }
    } 

    output.resize(max_width,max_height);
    for (unsigned int i = 0; i < base_pic->width(); i++)
    {
        for (unsigned int j = 0; j < base_pic->height(); j++)
        {
            output.getPixel(i,j)=base_pic->getPixel(i,j);
        }
        
    }
    

    for (unsigned i = 0; i < current_; i++)
    {
        if (array[i]->sticker_ == nullptr)
        {
            continue;
        }
        for (unsigned int j = 0; j < array[i]->sticker_->width(); j++)
        {
            for (unsigned int k = 0; k < array[i]->sticker_->height(); k++)
            {
                if (array[i]->sticker_->getPixel(j,k).a == 0)
                {
                    continue;
                }
                cs225::HSLAPixel & pixel = output.getPixel(j+array[i]->x_,k+array[i]->y_);
                pixel = array[i]->sticker_->getPixel(j,k);
                
            }
            
        }

    }
    
    return output;
    

}


Stickers::Stickers(/* args */)
{
    sticker_ = nullptr;
    x_ = 0;                    
    y_ = 0;
}

Stickers::~Stickers()
{
    if(sticker_!=nullptr)
    {
        delete sticker_;
        sticker_ = nullptr;
        x_ = 0;
        y_ = 0;
    }
}

Stickers::Stickers(Image & sticker, unsigned x, unsigned y)
{
    sticker_ = new Image(sticker);
    x_ = x;
    y_ = y;
}

StickerSheet::StickerSheet 	( 	const Image &  	picture, unsigned  	max ) 	
{
    current_ = 0;
    if (max<=0)
    {
        max_=0;
        array=nullptr;
    }
    else
    {
        max_ = max;
        array = new Stickers*[max_];
    }

    if (picture.width() && picture.height())
    {
        base_pic = new Image(picture);
    }
    else
    {
        base_pic = nullptr;
    }
    
}

StickerSheet::~StickerSheet 	( 		) 	
{
    clear();
}


StickerSheet::StickerSheet 	( 	const StickerSheet &  	other	) 	
{
    clear();
    copy(other);
}


int StickerSheet::addSticker 	( 	Image &  	sticker, unsigned  	x, unsigned  	y ) 
{
    if(current_<=max_)
    {
        for(unsigned i = 0; i<current_; i++)    
        {
            if (array[i]->sticker_ == nullptr)
            {
                delete array[i];
                array[i] = new Stickers(sticker, x, y);
                return i;
            }
            
        }

        if (current_ < max_)
        {
            array[current_] = new Stickers(sticker,x,y);
            current_++;
            return current_-1;

        }
        
        return -1;

    }

    return -1;


}	

void StickerSheet::changeMaxStickers 	( 	unsigned  	max	) 	
{
    if (max_ == max)
    {
        return;
    }

    unsigned current_temp = current_;

    Image* base_temp = new Image(*base_pic);

    Stickers** temp = new Stickers*[max];    

    if (current_ <= max)
    {
        for (unsigned i = 0; i < current_; i++)
        {
            if (array[i]->sticker_ == nullptr)
            {
                temp[i]= new Stickers();
                continue;
            }
            
            temp[i]=new Stickers(*(array[i]->sticker_),array[i]->x_,array[i]->y_);
        }

        clear();
        
        array = temp;
        temp = nullptr;
        current_ = current_temp;
        max_ = max;
        base_pic = base_temp;
        base_temp = nullptr;
        return;

    }

    else
    {
        for(unsigned j =0; j<max; j++)
        {
            if (array[j]->sticker_ == nullptr)
            {
                temp[j]= new Stickers();
                continue;
            }
            
            temp[j]=new Stickers(*(array[j]->sticker_),array[j]->x_,array[j]->y_);            
        }
        clear();
        array = temp;
        temp = nullptr;
        max_ = max;
        current_ = max;
        base_pic = base_temp;
        base_temp = nullptr;
        return;
    }

}

const StickerSheet & StickerSheet::operator= 	( 	const StickerSheet &  	other	) 	
{
    clear();
    copy(other);
    return *this;
}

void StickerSheet::removeSticker 	( 	unsigned  	index	) 	
{
    if(index>current_-1 || array[index]->sticker_ == nullptr)
    {
        return;
    }

    delete array[index]->sticker_;
    array[index]->sticker_ = nullptr;
    array[index]->x_ = 0;
    array[index]->y_ = 0;
    return;
}


bool StickerSheet::translate 	( 	unsigned  	index, unsigned  	x, unsigned  	y  ) 	
{
    if (index > current_-1 || array[index]->sticker_==nullptr)
    {
        return false;
    }
    
    array[index]->x_ = x;
    array[index]->y_ = y;
    return true;
}