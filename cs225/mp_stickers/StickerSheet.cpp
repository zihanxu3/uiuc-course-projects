#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>


using cs225::HSLAPixel;
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    //Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. More...
    base_image = new Image();
    *base_image = picture;
    this->max = max;
    x_axis = new unsigned[max];
    y_axis = new unsigned[max];
    image_arr = new Image*[max];
    for (unsigned i = 0; i < max; i++) {
        image_arr[i] = NULL;
    }
}

StickerSheet::~StickerSheet() {
    //Frees all space that was dynamically allocated by this StickerSheet. More...
    _destroy();
}
      
StickerSheet::StickerSheet(const StickerSheet &other) {
    //The copy constructor makes this StickerSheet an independent copy of the source. More...
    _copy(other);
}
      
const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    //The assignment operator for the StickerSheet class. More...
    if (this != &other) {
        _destroy();
        _copy(other);
    }
    return *this;
}
      
void StickerSheet::changeMaxStickers(unsigned max) {
    //Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. More...
    unsigned *nx_axis = new unsigned[max];
    unsigned *ny_axis = new unsigned[max];
    Image** nimage_arr = new Image*[max];
    for (unsigned i = 0; i < max; i++) {
        nimage_arr[i] = NULL;
    }
    unsigned count = _countImage();
    if (count > max) {
        //assign the largest of the two
        count = max;
    }
    
    for (unsigned i = 0; i < count; i++) {
        if (image_arr[i] != NULL) {
            nimage_arr[i] = this->image_arr[i];
            nx_axis[i] = this->x_axis[i];
            ny_axis[i] = this->y_axis[i];
        }
    }
    //delete previous info
    delete[] x_axis;
    delete[] y_axis;
    delete[] image_arr;
    
    //assign new info to this
    x_axis = nx_axis;
    y_axis = ny_axis;
    image_arr = nimage_arr;
    this->max = max;

}
      
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    //Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. More...
    for (unsigned i = 0; i < max; i++) {
        if (image_arr[i] == NULL) {
            image_arr[i] = &sticker;
            x_axis[i] = x;
            y_axis[i] = y;
            return i;
        }
    }
    return -1;
}
      
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    //Changes the x and y coordinates of the Image in the specified layer. More...
    if (index < max && index >= 0) {
        if (image_arr[index] != NULL) {
            x_axis[index] = x;
            y_axis[index] = y;
            return true;
        }
    }
    return false;
}
      
void StickerSheet::removeSticker(unsigned index) {
    //Removes the sticker at the given zero-based layer index. More...
    if (index < max && index >= 0) {
        image_arr[index] = NULL;
        x_axis[index] = 0;
        x_axis[index] = 0;
    }
}
      
Image* StickerSheet::getSticker(unsigned index) {
    //Returns a pointer to the sticker at the specified index, not a copy of it. More...
    if (index < max && index >= 0) {
        if (image_arr[index] != NULL) {
            return image_arr[index];
        }
    }
    return NULL;
}
      
Image StickerSheet::render() const {
    //Renders the whole StickerSheet on one Image and returns that Image. More...
    unsigned max_down = 0;
    unsigned max_right = 0;
    for (unsigned i = 0; i < max; i++) {
        if (image_arr[i] != NULL) {
            unsigned width = (*image_arr[i]).width();
            unsigned height = (*image_arr[i]).height();
            unsigned down = height + y_axis[i];
            unsigned right = width + x_axis[i];
            if (down >= max_down) {
                max_down = down;
            }
            if (right >= max_right) {
                max_right = right;
            }
        }
    }
    unsigned final_width = max_right > base_image -> width() ? max_right : base_image -> width();
    unsigned final_height = max_down > base_image -> height() ? max_down : base_image -> height();

    Image final_image;
    final_image.resize(final_width, final_height);
    
    for (unsigned a = 0; a < (*base_image).width(); a++) {
        for (unsigned b = 0; b < (*base_image).height(); b++) {
            HSLAPixel &final_p = final_image.getPixel(a, b);
            HSLAPixel &base_p = (*base_image).getPixel(a, b);
            if (base_p.a != 0) {
                final_p = base_p;
            }
        }
    }
    for (unsigned k = 0; k < max; k++) {
        if (image_arr[k] != NULL) {
            for (unsigned m = 0; m < (*image_arr[k]).width(); m++) {
                for (unsigned n = 0; n < (*image_arr[k]).height(); n++) {
                    HSLAPixel &final_p = final_image.getPixel(m + x_axis[k], n + y_axis[k]);
                    HSLAPixel &sti_p = (*image_arr[k]).getPixel(m, n);
                    if (sti_p.a != 0) {
                        final_p = sti_p;
                    }
                }
            }
        }
    }
    return final_image;
}


//MARK: helper function

void StickerSheet::_destroy() {
    delete base_image;
    delete[] x_axis;
    delete[] y_axis;
    delete[] image_arr;
}

StickerSheet & StickerSheet::_copy(const StickerSheet &other) {
    base_image = new Image();
    *base_image = *(other.base_image);
    
    max = other.max;
    x_axis = new unsigned[max];
    y_axis = new unsigned[max];
    image_arr = new Image*[max];
    

    //have to initialize to NULL
    for (unsigned i = 0; i < max; i++) {
        image_arr[i] = NULL;
    }
    for (unsigned j = 0; j < max; j++) {
        if (other.image_arr[j] != NULL) {
            x_axis[j] = other.x_axis[j];
            y_axis[j] = other.y_axis[j];
            image_arr[j] = other.image_arr[j];
        }
    }

    return *this;
}

unsigned StickerSheet::_countImage() {
    unsigned count = 0;
    for (unsigned i = 0; i < max; i++) {
        if (image_arr[i] != NULL) {
            count++;
        }
    }
    return count;
}
