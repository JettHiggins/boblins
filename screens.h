#include "raylib.h"

#ifndef SCREENS_H
#define SCREENS_H

enum GameScreen { UNKNOWN = -1, LOGO = 0, GAME = 1 };

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitLogoScreen();
void UpdateLogoScreen();
void DrawLogoScreen();
void UnloadLogoScreen();
int FinishLogoScreen();

#endif // SCREENS_H
