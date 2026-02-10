#include "../../include/io/input.h"

#include <stdarg.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

void initKeyMap(void)
{
    keyMap.exit.action = EXIT;
    keyMap.up.action = UP;
    keyMap.down.action = DOWN;
    keyMap.left.action = LEFT;
    keyMap.right.action = RIGHT;

    // The 'keys' function of each action represents which keys activate the action.
    // They are malloc'd to the size of an integer times the number of keys per action.
    // Right now, each action can only support up to two keys but that can change.

    keyMap.exit.keys = malloc(sizeof(int) * 2);
    constexpr int exitKeys[2] = { GLFW_KEY_ESCAPE, GLFW_KEY_ESCAPE };
    memcpy(keyMap.exit.keys, exitKeys, sizeof(int) * 2);

    keyMap.up.keys = malloc(sizeof(int) * 2);
    constexpr int upKeys[2] = { GLFW_KEY_W, GLFW_KEY_UP };
    memcpy(keyMap.up.keys, upKeys, sizeof(int) * 2);

    keyMap.down.keys = malloc(sizeof(int) * 2);
    constexpr int downKeys[2] = { GLFW_KEY_S, GLFW_KEY_DOWN };
    memcpy(keyMap.down.keys, downKeys, sizeof(int) * 2);

    keyMap.left.keys = malloc(sizeof(int) * 2);
    constexpr int leftKeys[2] = { GLFW_KEY_A, GLFW_KEY_LEFT };
    memcpy(keyMap.left.keys, leftKeys, sizeof(int) * 2);

    keyMap.right.keys = malloc(sizeof(int) * 2);
    constexpr int rightKeys[2] = { GLFW_KEY_A, GLFW_KEY_LEFT };
    memcpy(keyMap.right.keys, rightKeys, sizeof(int) * 2);
}

static int* getActionKeys(const KeyAction action)
{
    int* actionKeys = malloc(sizeof(int) * 2);

    switch (action) {
        case EXIT:
            memcpy(actionKeys, keyMap.exit.keys, sizeof(int) * 2);
            break;
        case UP:
            memcpy(actionKeys, keyMap.up.keys, sizeof(int) * 2);
            break;
        case DOWN:
            memcpy(actionKeys, keyMap.down.keys, sizeof(int) * 2);
            break;
        case LEFT:
            memcpy(actionKeys, keyMap.left.keys, sizeof(int) * 2);
            break;
        case RIGHT:
            memcpy(actionKeys, keyMap.right.keys, sizeof(int) * 2);
            break;
        default:
            free(actionKeys);
            return nullptr;
    }

    return actionKeys;
}

bool actionPressed(const KeyAction action)
{
    int* keys = getActionKeys(action);

    if (keys == nullptr) {
        free(keys);
        return false;
    }

    int state = 0;
    for (int i = 0; i < 2; i++) {
        state = glfwGetKey(instance.window, keys[i]);
        if (state == GLFW_PRESS) {
            free(keys);
            return true;
        }
    }

    free(keys);
    return false;
}

bool actionReleased(const KeyAction action)
{
    int* keys = getActionKeys(action);

    if (keys == nullptr) {
        free(keys);
        return false;
    }

    static bool fPressed = false;

    int state = 0;
    for (int i = 0; i < 2; i++) {
        state = glfwGetKey(instance.window, keys[i]);
        if (state == GLFW_PRESS) {
            fPressed = true;
        }
    }

    for (int i = 0; i < 2; i++) {
        state += glfwGetKey(instance.window, keys[i]);
        if (state == GLFW_RELEASE && fPressed) {
            fPressed = false;
            free(keys);
            return true;
        }
    }

    free(keys);
    return false;
}

bool actionJustPressed(const KeyAction action)
{
    static bool fPressed = false;

    if (actionPressed(action) && !fPressed) {
        fPressed = true;
        return true;
    }

    if (!actionPressed(action)) {
        fPressed = false;
    }

    return false;
}

bool actionsPressed(const int numActions, ...)
{
    va_list args;
    va_start(args, numActions);

    int keysPressed = 0;
    for (int i = 0; i < numActions; i++) {
        keysPressed += actionPressed(va_arg(args, int));
    }

    if (keysPressed == numActions) {
        return true;
    }

    va_end(args);

    return false;
}

void cleanUpInput(void)
{
    free(keyMap.exit.keys);
    free(keyMap.up.keys);
    free(keyMap.down.keys);
    free(keyMap.left.keys);
    free(keyMap.right.keys);
}