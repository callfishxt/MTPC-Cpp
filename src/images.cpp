#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "images.hpp"

void save_alpha_channel(const std::string& filename) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, 4);

    if (image) {
        stbi_write_png(filename.c_str(), width, height, 4, image, width * 4);
        stbi_image_free(image);
        std::cout << "[I] <images> successfully saved alpha channel for " << filename << std::endl;
    } else {
        std::cerr << "[E] <images> failed to load image: " << filename << std::endl;
    }
}

void colorize(const std::string& src_path, const std::string& dest_path) {
    int width, height, channels;
    unsigned char* grass_texture = stbi_load(src_path.c_str(), &width, &height, &channels, 4);

    
    if (grass_texture) {
        float brightness_factor = 0.69f;
        float saturation_factor = 1.8f;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * 4;
                unsigned char r = grass_texture[index];
                unsigned char g = grass_texture[index + 1];
                unsigned char b = grass_texture[index + 2];
                unsigned char a = grass_texture[index + 3];

                if (a != 0) {
                    int new_r = static_cast<int>(r * brightness_factor);
                    int new_g = static_cast<int>(std::min(g + 40, 255) * brightness_factor);
                    int new_b = static_cast<int>(b * brightness_factor);

                    float h, s, v;
                    float max = std::max(std::max(new_r, new_g), new_b) / 255.0f;
                    float min = std::min(std::min(new_r, new_g), new_b) / 255.0f;
                    v = max;
                    float delta = max - min;

                    if (max != 0) {
                        s = (max == min) ? 0 : delta / max;
                    } else {
                        s = 0;
                        h = -1;
                    }

                    if (delta != 0) {
                        if (max == new_r / 255.0f) {
                            h = (new_g - new_b) / delta;
                        } else if (max == new_g / 255.0f) {
                            h = 2 + (new_b - new_r) / delta;
                        } else {
                            h = 4 + (new_r - new_g) / delta;
                        }
                        h *= 60;
                        if (h < 0) h += 360;
                    }

                    s = std::min(s * saturation_factor, 1.0f);

                    float r_out, g_out, b_out;
                    if (s == 0) {
                        r_out = g_out = b_out = v * 255;
                    } else {
                        float f = (h / 60);
                        int i = static_cast<int>(f);
                        float f_part = f - i;
                        int p = static_cast<int>(v * (1 - s) * 255);
                        int q = static_cast<int>(v * (1 - f_part * s) * 255);
                        int t = static_cast<int>(v * (1 - (1 - f_part) * s) * 255);
                        v *= 255;

                        switch (i % 6) {
                            case 0: r_out = v; g_out = t; b_out = p; break;
                            case 1: r_out = q; g_out = v; b_out = p; break;
                            case 2: r_out = p; g_out = v; b_out = t; break;
                            case 3: r_out = p; g_out = q; b_out = v; break;
                            case 4: r_out = t; g_out = p; b_out = v; break;
                            case 5: r_out = v; g_out = p; b_out = q; break;
                        }
                    }

                    grass_texture[index] = static_cast<unsigned char>(std::min(static_cast<int>(r_out), 255));
                    grass_texture[index + 1] = static_cast<unsigned char>(std::min(static_cast<int>(g_out), 255));
                    grass_texture[index + 2] = static_cast<unsigned char>(std::min(static_cast<int>(b_out * 150 / 255.0f), 255));
                    grass_texture[index + 3] = a;
                }
            }
        }

        stbi_write_png(dest_path.c_str(), width, height, 4, grass_texture, width * 4);
        stbi_image_free(grass_texture);
        std::cout << "[I] <images> successfully colorized texture for " << src_path << std::endl;
    } else {
        std::cerr << "[E] <images> failed to load texture: " << src_path << std::endl;
    }


}