//
// Created by Kimin on 2023/8/10.
//

#ifndef CML_IMAGE_H
#define CML_IMAGE_H

#include <fstream>
#include <iostream>

using namespace std;

#pragma pack(push, 1)

struct BMPHeader {
    // bmp file header
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;

    // bmp info header
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t dataSize;
    int32_t horizontalResolution;
    int32_t verticalResolution;
    uint32_t colors;
    uint32_t importantColors;
};
#pragma pack(pop)

class Image {
private:
    BMPHeader _header{};
    uint8_t *_palette{};
    uint8_t *_pixels{};
    uint8_t ***rgba = new uint8_t **[4];

public:
    // constructor & destructor
    Image() = default;

    explicit Image(const char *path);

    ~Image() = default;

    // methods
    bool open(const char *path);

    void parse1();

    void parse4();

    void parse8();

    void parse16();

    void parse24();

    void parse32();

    // get data
    [[nodiscard]] BMPHeader header() const;

    [[nodiscard]] int32_t height() const;

    [[nodiscard]] int32_t width() const;

    [[nodiscard]] uint32_t size() const;

    [[nodiscard]] uint16_t bpp() const;

    uint8_t *pixel();

    uint8_t **bData();

    uint8_t **rData();

    uint8_t **gData();

    uint8_t **aData();

    uint8_t *palette();
};


#endif //CML_IMAGE_H
