#include <iostream>
#include "bmp.h"

int main() {
    const int width = 0x100;
    const int height = 0x100;
    // Pixels are stored in a 2D array
    RGB24** pixels = new RGB24*[width];

    // Generate pixels for the image
    // This results in a cool gradient effect
    for (int i = 0; i < height; i++) {
        pixels[i] = new RGB24[width];
        for (int j = 0; j < width; j++) {
            pixels[i][j] = {static_cast<uint8_t>(j), static_cast<uint8_t>(i), static_cast<uint8_t>(j)};
        }
    }

    BMPImage bmp(&pixels, width, height);
    std::string imagePath = "example.bmp";
    bmp.WriteImageToFile(imagePath);
    std::cout << "Image generated!" << std::endl;

    system(imagePath.c_str()); // open image

    delete[] pixels;
    return EXIT_SUCCESS;
}