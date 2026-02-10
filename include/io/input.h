#pragma once

#include <GLFW/glfw3.h>

#include "global.h"

void initKeyMap(void);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
bool actionPressed(KeyAction action);
bool actionReleased(KeyAction action);
bool actionJustPressed(KeyAction action);
bool actionsPressed(int numActions, ...);
void cleanUpInput(void);
