#include "graphics/image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLFW/glfw3.h>

#include "logger/logger.h"

unsigned char* loadImage(const char* filepath, int* width, int* height)
{
    unsigned char *image = stbi_load(filepath, width, height, nullptr, 4);

    if (image == nullptr) {
        logERROR("Failed to load image: %s\n", filepath);
    }

    return image;
}

GLFWimage loadImageForGlfw(const char* filepath)
{
    int width, height;
    unsigned char* imageData = loadImage(filepath, &width, &height);

    GLFWimage image;
    image.pixels = imageData;
    image.width = width;
    image.height = height;

    return image;
}

void freeImage(unsigned char* image)
{
    stbi_image_free(image);
}
