#include "core/window.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "global.h"
#include "graphics/image.h"
#include "logger/logger.h"

double currentFrame;
double lastFrame;

static void errorCallback(const int error, const char* description)
{
    logERROR("%d - %s\n", error, description);
}

static void frameBufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    UNUSED(window);
    glViewport(0, 0, width, height);
}

void windowInit(const int width, const int height, const char* title, void (*returnValSet)(int))
{
    instance.width = width;
    instance.height = height;
    instance.title = title;
    instance.vsync = 1;
    instance.running = true;

    if (!glfwInit()) {
        logERROR("Failed to initialize GLFW!\n");
        returnValSet(1);
        return;
    }

    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    instance.window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!instance.window) {
        logERROR("Failed to create GLFW window!\n");
        glfwTerminate();
        returnValSet(2);
        return;
    }

    // glfwSetKeyCallback(instance.window, keyCallback);
    glfwSetFramebufferSizeCallback(instance.window, frameBufferSizeCallback);

    glfwMakeContextCurrent(instance.window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(instance.vsync);

    glfwFocusWindow(instance.window);


    // TODO: Move this elsewhere!
    GLFWimage images[2];
    images[0] = loadImageForGlfw("../assets/icon.png");
    images[1] = loadImageForGlfw("../assets/icon_small.png");

    glfwSetWindowIcon(instance.window, 2, images);

    freeImage(images[0].pixels);
    freeImage(images[1].pixels);

    currentFrame = glfwGetTime();
    lastFrame = currentFrame;
}

void cleanUpWindow(void)
{
    glfwDestroyWindow(instance.window);
    glfwTerminate();
}

void pollEvents(void)
{
    if (glfwWindowShouldClose(instance.window))
        closeGame();

    glfwPollEvents();
}

void closeGame(void)
{
    instance.running = false;
    glfwSetWindowShouldClose(instance.window, instance.running);
}

void calculateDelta(double* deltaTime)
{
    currentFrame = glfwGetTime();
    *deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
