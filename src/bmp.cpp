#include "bmp.h"

BMPImage::BMPImage(RGB24*** pixels, int w, int h) {
    pixels_ = pixels;
    width_ = w;
    height_ = h;
    padding_ = (4 - (width_ * 3) % 4) % 4;
    fileSize_ = bitmapFileHeaderSize_ + dibHeaderSize_ + height_ * width_ * 3 + padding_ * height_;
    pixelArrayOffset_ = bitmapFileHeaderSize_ + dibHeaderSize_;
}

void BMPImage::WriteImageToFile(const std::string& fileName) {
    uint32_t empty = 0x00000000;
    std::ofstream file(fileName, std::ios::out | std::ios::binary);
    // BitmapFileHeader
    file.write("BM", 2); // magic number
    file.write((char*)&fileSize_, 4);
    file.write((char*)&empty, 4); // reserved
    file.write((char*)&pixelArrayOffset_, 4);

    // DIB
    file.write((char*)&dibHeaderSize_, 4);
    file.write((char*)&width_, 4);
    file.write((char*)&height_, 4);
    uint16_t colorPlanes = 1;
    file.write((char*)&colorPlanes, 2);
    uint16_t bitsPerPixel = 24; // 24-bit RGB
    file.write((char*)&bitsPerPixel, 2);
    file.write((char*)&empty, 4); // compression, 0 for none
    file.write((char*)&empty, 4); // ignore without compression
    file.write((char*)&empty, 4); // ignore
    file.write((char*)&empty, 4); // ignore
    file.write((char*)&empty, 4); // number of colors in color palette
    file.write((char*)&empty, 4); // important colors

    // Iterate all pixels
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            // Colors in BGR order
            file.write((char*)&(*pixels_)[i][j].b, 1);
            file.write((char*)&(*pixels_)[i][j].g, 1);
            file.write((char*)&(*pixels_)[i][j].r, 1);
        }
        // Row padding (a row must be n * 4 bytes)
        file.write((char*)&empty, padding_);
    }
}