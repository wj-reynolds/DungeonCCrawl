#pragma once
#include "mesh.h"
#include "shader.h"

typedef struct RenderCommand_S {
    Mesh *mesh;
    Shader *shader;
} RenderCommand;

typedef struct RenderQueue_S {
    int count;
    RenderCommand *commands;
} RenderQueue;


void initRenderer(void);
void setWireFrame(bool wireframe);
void setClearColor(float r, float g, float b, float a);
void addRenderCommand(RenderCommand command);
void renderFrame(void);