#include "crawl.h"

#include "core/window.h"
#include "io/fileio.h"
#include "io/input.h"
#include "graphics/mesh.h"
#include "graphics/render.h"
#include "graphics/shader.h"
#include "logger/logger.h"


static void init(void)
{
    setDateAndTime(false);
    initKeyMap();
    initRenderer();
    parseOptions("../options.txt");
}

static void processInput(void)
{
    if (actionPressed(EXIT))
        closeGame();
}

static void update(const double delta)
{
    UNUSED(delta);

    pollEvents();
}

static void draw(const double delta)
{
    UNUSED(delta);
    renderFrame();
}

static void gameLoop(void)
{
    double deltaTime = 0;

    // Test mesh
    constexpr float vertices[] = {
        -0.5f,  -0.5f,  0.0f,
         0.0f,   0.5f,  0.0f,
         0.5f,  -0.5f,  0.0f
    };

    Mesh testMesh = { 0 };
    testMesh = generateMesh(vertices, 3, 3);

    // Test mesh 2
    constexpr float vertices2[] = {
        -0.9f,  -0.9f,  -0.4f,
         -0.4f,   0.1f,  -0.4f,
         0.1f,  -0.9f,  -0.4f
    };

    Mesh testMesh2 = { 0 };
    testMesh2 = generateMesh(vertices2, 3, 3);

    // Test mesh 3
    constexpr float vertices3[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    constexpr uint32_t elements[] = {
        3, 2, 1,
        1, 0, 3
    };

    Mesh testMesh3 = { 0 };
    testMesh3 = generateMeshI(vertices3, 4, 3, elements, 6);

    // Test shader
    const char* vertexShader = readShaderFile("../shaders/vert.glsl");
    const char* fragmentShader = readShaderFile("../shaders/frag.glsl");

    Shader testShader = { 0 };
    testShader = createShader(vertexShader, fragmentShader);

    setUniformFloat3("color", 0.2588f, 0.5294f, 0.9608f, testShader);

    const RenderCommand testRenderCommand = { &testMesh, &testShader};
    const RenderCommand testRenderCommand2 = { &testMesh2, &testShader};
    const RenderCommand testRenderCommand3 = { &testMesh3, &testShader};

    while (instance.running) {
        calculateDelta(&deltaTime);

        processInput();
        update(deltaTime);
        draw(deltaTime);
        addRenderCommand(testRenderCommand);
        addRenderCommand(testRenderCommand2);
        addRenderCommand(testRenderCommand3);
    }

    cleanUpMesh(&testMesh);
    cleanUpShader(&testShader);
    cleanUpMesh(&testMesh2);
    cleanUpMesh(&testMesh3);

}

static void deinitialize(void)
{
    cleanUpWindow();
    cleanUpInput();
}

void run(const int width, const int height, const char* title, void (*returnValSet)(int))
{
    windowInit(width, height, title, returnValSet);
    init();

    gameLoop();

    deinitialize();
}