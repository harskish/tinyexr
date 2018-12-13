#include <iostream>
#include <fstream>
#include <string>

#define TINYEXR_IMPLEMENTATION
#include "../tinyexr.h"

void savePfm(const char* path, const float* img, int w, int h, int channels)
{
    if (channels != 1 && channels != 3)
        exit(-1);

    std::ofstream out(path, std::ios::binary);
    if (!out)
        exit(-1);

    out << ((channels == 1) ? "Pf" : "PF") << '\n';
    out << w << " " << h << '\n';
    out << -1.0 << '\n';
    for (int y = 0; y < h; ++y)
        out.write(reinterpret_cast<const char *>(img + (h - y - 1)*w*channels), w*channels * sizeof(float));
}

float* loadExr(const char* path, int& w, int& h) {
    const char* err = NULL;
    
    float* rgba;
    int ret = LoadEXR(&rgba, &w, &h, path, &err);
    if (ret != 0) {
        std::cerr << "EXR loading failed: " << err << std::endl;
        exit(-1);
    }

    // Convert from RGBA to RGB
    float* dst = new float[w*h * 3];
    for (int i = 0; i < w*h; i++) {
        dst[i * 3 + 0] = rgba[i * 4 + 0];
        dst[i * 3 + 1] = rgba[i * 4 + 1];
        dst[i * 3 + 2] = rgba[i * 4 + 2];
    }

    free(rgba);

    return dst;
}

int main(int argc, char* argv[]) {
    int w, h;
    float* pixels;

    pixels = loadExr("broken.exr", w, h);
    savePfm("output.pfm", pixels, w, h, 3);
    delete[] pixels;

    std::cout << w << "x" << h << std::endl;
    std::cout << "Done" << std::endl;
    return 0;
}