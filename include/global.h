#pragma once

#include "GLFW/glfw3.h"

// From Stackoverflow -- https://stackoverflow.com/questions/23235910/variadic-unused-function-macro
// Answer by kugel and edited by Michael.
// Awesome Unused Macro
#define UNUSED0()
#define UNUSED1(a)                  (void)(a)
#define UNUSED2(a,b)                (void)(a),UNUSED1(b)
#define UNUSED3(a,b,c)              (void)(a),UNUSED2(b,c)
#define UNUSED4(a,b,c,d)            (void)(a),UNUSED3(b,c,d)
#define UNUSED5(a,b,c,d,e)          (void)(a),UNUSED4(b,c,d,e)

#define VA_NUM_ARGS_IMPL(_0,_1,_2,_3,_4,_5, N,...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(100, ##__VA_ARGS__, 5, 4, 3, 2, 1, 0 )

#define ALL_UNUSED_IMPL_(nargs) UNUSED ## nargs
#define ALL_UNUSED_IMPL(nargs) ALL_UNUSED_IMPL_(nargs)
#define UNUSED(...) ALL_UNUSED_IMPL( VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__ )

typedef struct Instance_S {
    int width, height;
    const char* title;
    bool running;
    int vsync;
    GLFWwindow* window;
} Instance;

typedef enum KeyAction_E{
    NONE = 0,
    EXIT = 1,
    UP = 2,
    DOWN = 3,
    LEFT = 4,
    RIGHT = 5,
    NUM_KEYS    // Will always be equal to the number of keys above!
} KeyAction;

typedef struct KeyBind_S {
    KeyAction action;
    int* keys;
    // int numKeys;
} KeyBind;

typedef struct KeyMap_S {
    KeyBind exit;
    KeyBind up;
    KeyBind down;
    KeyBind left;
    KeyBind right;
} KeyMap;

extern Instance instance;
extern KeyMap keyMap;
