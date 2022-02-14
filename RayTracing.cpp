#include <iostream>
#include "Vector3.h"
#include "Color.h"

int main() {
    const int imageWidth = 256;
    const int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << '\n' << "255\n";

    Color color;
    color.B = 0.25f;

    for (int i = imageHeight - 1; i >= 0; i--) {
        std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            color.R = static_cast<float>(j) / (imageWidth - 1);
            color.G = static_cast<float>(i) / (imageHeight - 1);

            WriteColor(std::cout, color);
        }
    }

    std::cerr << "\nDone\n";
}
