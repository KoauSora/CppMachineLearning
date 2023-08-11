//
// Created by Kimin on 2023/8/10.
//

#include "Image.h"

// constructor & destructor
Image::Image(const char *path) {
    open(path);
}


// methods
bool Image::open(const char *path) {
    ifstream in(path, ios::binary);
    if (!in || !in.is_open()) {
        return false;
    }
    in.read(reinterpret_cast<char *>(&_header), sizeof(_header));
    if (_header.dataOffset != 54) {
        _palette = new uint8_t[_header.dataOffset - 54];
        in.read(reinterpret_cast<char *>(_palette), _header.dataOffset - 54);
    }
    _pixels = new uint8_t[_header.fileSize];
    in.read(reinterpret_cast<char *>(_pixels), _header.fileSize);
    in.close();

    switch (_header.bitsPerPixel) {
        case 1:
            parse1();
            break;
        case 4:
            parse4();
            break;
        case 8:
            parse8();
            break;
        case 16:
            parse16();
            break;
        case 24:
            parse24();
            break;
        case 32:
            parse32();
            break;
        default:
            break;
    }
    return true;
}

void Image::parse1() {
    int zeros = (32 - (_header.bitsPerPixel * _header.width) % 32) % 32;

}

void Image::parse4() {
    parse1();
}

void Image::parse8() {
    parse1();
}

void Image::parse16() {

}

void Image::parse24() {
    uint8_t Bpp = bpp() / 8;
    int zeros = (4 - (Bpp * _header.width % 4)) % 4;
    for (int i = 0; i < bpp() / 8; ++i) {
        rgba[i] = new uint8_t *[height()];
        for (int j = 0; j < height(); ++j) {
            rgba[i][j] = new uint8_t[width()];
            for (int k = 0; k < width(); ++k) {
                rgba[i][j][k] = _pixels[width() * j * Bpp + zeros * j + k * Bpp + i];
            }
        }
    }
}

void Image::parse32() {
    parse24();
}

// get data
BMPHeader Image::header() const {
    return _header;
}

uint8_t *Image::pixel() {
    return _pixels;
}

int32_t Image::height() const {
    return _header.height;
}

int32_t Image::width() const {
    return _header.width;
}

uint32_t Image::size() const {
    return _header.fileSize;
}

uint16_t Image::bpp() const {
    return _header.bitsPerPixel;
}

uint8_t **Image::bData() {
    return rgba[0];
}

uint8_t **Image::gData() {
    return rgba[1];
}

uint8_t **Image::rData() {
    return rgba[2];
}

uint8_t **Image::aData() {
    return rgba[3];
}

uint8_t *Image::palette() {
    return _palette;
}









