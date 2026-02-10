#include "graphics/shader.h"

#include <glad/gl.h>

#include "logger/logger.h"

Shader createShader(const char* vertex, const char* fragment)
{
    Shader shader = { 0 };
    shader.mProgramId = glCreateProgram();

    int status = GL_FALSE;
    char errorLog[1024];

    const uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSource = vertex;
    glShaderSource(vertexShaderId, 1, &vertexSource, nullptr);
    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        glGetShaderInfoLog(vertexShaderId, sizeof(errorLog), nullptr, errorLog);
        logERROR("Error compiling vertex shader: %s\n", vertex);
        logERROR(errorLog);
        glDeleteShader(vertexShaderId);
        return shader;
    }

    glAttachShader(shader.mProgramId, vertexShaderId);


    const uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentSource = fragment;
    glShaderSource(fragmentShaderId, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        glGetShaderInfoLog(fragmentShaderId, sizeof(errorLog), nullptr, errorLog);
        logERROR("Error compiling fragment shader: %s\n", fragment);
        logERROR(errorLog);
        glDeleteShader(fragmentShaderId);
        return shader;
    }

    glAttachShader(shader.mProgramId, fragmentShaderId);

    glLinkProgram(shader.mProgramId);
    glValidateProgram(shader.mProgramId);
    glGetProgramiv(shader.mProgramId, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        glGetProgramInfoLog(shader.mProgramId, sizeof(errorLog), nullptr, errorLog);
        logERROR("Error linking shader program: \n%s\n", errorLog);
        glDeleteProgram(shader.mProgramId);
        shader.mProgramId = -1;
        return shader;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    logINFO("Shader successfully created!\n");

    return shader;
}

void bindShader(const Shader shader)
{
    glUseProgram(shader.mProgramId);
}

void unbindShader()
{
    glUseProgram(0);
}

static int getUniformLocation(const char* name, const Shader shader)
{
    // TODO: Find a way to cache this. Perhaps a dynamic
    // TODO: array of some sorts.
    return glGetUniformLocation(shader.mProgramId, name);
}

void setUniformInt(const char* name, const int value, const Shader shader)
{
    glUseProgram(shader.mProgramId);
    glUniform1i(getUniformLocation(name, shader), value);
}

void setUniformFloat(const char* name, const float value, const Shader shader)
{
    glUseProgram(shader.mProgramId);
    glUniform1f(getUniformLocation(name, shader), value);
}

void setUniformFloat2(const char* name, const float value, const float value2, const Shader shader)
{
    glUseProgram(shader.mProgramId);
    glUniform2f(getUniformLocation(name, shader), value, value2);
}

void setUniformFloat3(const char* name, const float value, const float value2, const float value3, const Shader shader)
{
    glUseProgram(shader.mProgramId);
    glUniform3f(getUniformLocation(name, shader), value, value2, value3);
}

void setUniformFloat4(const char* name, const float value, const float value2, const float value3, const float value4, const Shader shader)
{
    glUseProgram(shader.mProgramId);
    glUniform4f(getUniformLocation(name, shader), value, value2, value3, value4);
}

void cleanUpShader(const Shader* shader)
{
    glUseProgram(0);
    glDeleteProgram(shader->mProgramId);
}
