#pragma once
#include <iostream>
#include <cstdint>
#include <fstream>

// 24-bit RGB color
struct RGB24 {
    uint8_t r, g, b;
};

class BMPImage {
private:
    RGB24*** pixels_; // Pointer to a 2D pixel array
    int width_;
    int height_;
    int bitmapFileHeaderSize_ = 14;
    int dibHeaderSize_ = 40;
    int padding_;
    int fileSize_;
    int pixelArrayOffset_;
public:
    BMPImage(RGB24***, int, int);
    void WriteImageToFile(const std::string&);
};