#pragma once

void windowInit(int width, int height, const char* title, void (*returnValSet)(int));
void cleanUpWindow(void);
void pollEvents(void);
void closeGame(void);
void calculateDelta(double* deltaTime);