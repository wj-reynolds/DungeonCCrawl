#pragma once
#include <GLFW/glfw3.h>

unsigned char* loadImage(const char* filepath, int* width, int* height);
GLFWimage loadImageForGlfw(const char* filepath);
void freeImage(unsigned char* image);