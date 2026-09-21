#include "game_types.hpp"

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#pragma once


namespace Renderer {
  extern Camera3D camera;
  void unloadRenderer();
  void initRenderer();
  void drawGame(const Thing* things);
};

namespace Update {
  extern Thing things[];
  void initGame(Bounds bound);
  void updateGame();
}

namespace Utils { 
  void printVec3(Vector3 vec);
};
