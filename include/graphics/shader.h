#pragma once
#include <stdint.h>

typedef struct Shader_T {
    uint32_t mProgramId;
} Shader;

Shader createShader(const char* vertex, const char* fragment);
void bindShader(Shader shader);
void unbindShader();
void setUniformInt(const char* name, int value, Shader shader);
void setUniformFloat(const char* name, float value, Shader shader);
void setUniformFloat2(const char* name, float value, float value2, Shader shader);
void setUniformFloat3(const char* name, float value, float value2, float value3, Shader shader);
void setUniformFloat4(const char* name, float value, float value2, float value3, float value4, Shader shader);
void cleanUpShader(const Shader* shader);

