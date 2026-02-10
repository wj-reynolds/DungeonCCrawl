#include "graphics/render.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "logger/logger.h"

RenderQueue commandQueue;

static void renderMesh(const Mesh* mesh, const Shader* shader)
{
    if (mesh == nullptr || shader == nullptr) {
        logWARNING("Attempting to use invalid mesh or shader data!\n");
        return;
    }

    bindMesh(*mesh);
    bindShader(*shader);

    if (mesh->elementCount > 0) {
        glDrawElements(GL_TRIANGLES, (int) mesh->elementCount, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (int) mesh->vertexCount);
    }

    unbindShader();
    unbindMesh();
}

void initRenderer(void)
{
    logINFO("Initializing renderer...\n");
    logINFO("---OpenGL INFO---\n");
    logINFO("Vendor: %s\n", glGetString(GL_VENDOR));
    logINFO("Version: %s\n", glGetString(GL_VERSION));
    logINFO("Renderer: %s\n", glGetString(GL_RENDERER));

    // Initialize OpenGL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    setClearColor(0.1529f, 0.5490f, 0.2392f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    commandQueue.count = 0;
}

void setWireFrame(const bool wireframe)
{
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void setClearColor(const float r, const float g, const float b, const float a)
{
    glClearColor(r, g, b, a);
}

static void clearFrame(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void addRenderCommand(const RenderCommand command)
{
    RenderCommand *tmpValues = malloc(sizeof(RenderCommand) * commandQueue.count);
    memcpy(tmpValues, commandQueue.commands, sizeof(RenderCommand) * commandQueue.count);

    free(commandQueue.commands);
    commandQueue.count += 1;
    commandQueue.commands = malloc(sizeof(RenderCommand) * commandQueue.count);

    for (int i = 0; i < commandQueue.count - 1; i++) {
        commandQueue.commands[i] = tmpValues[i];
    }

    commandQueue.commands[commandQueue.count - 1] = command;

    free(tmpValues);
}

static void popCommand(void)
{
    RenderCommand *tmpValues = malloc(sizeof(RenderCommand) * commandQueue.count);
    memcpy(tmpValues, commandQueue.commands, sizeof(RenderCommand) * commandQueue.count);

    free(commandQueue.commands);
    commandQueue.count -= 1;
    commandQueue.commands = malloc(sizeof(RenderCommand) * commandQueue.count);

    for (int i = 0; i < commandQueue.count; i++) {
        commandQueue.commands[i] = tmpValues[i];
    }

    free(tmpValues);
}

void renderFrame(void)
{
    clearFrame();

    while (commandQueue.count > 0) {
        const int i = commandQueue.count - 1;
        renderMesh(commandQueue.commands[i].mesh, commandQueue.commands[i].shader);
        popCommand();
    }

    glfwSwapBuffers(instance.window);
}