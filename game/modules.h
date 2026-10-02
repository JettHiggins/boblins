#include "game_types.hpp"

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#pragma once


namespace Renderer {
  extern Camera3D camera;
  extern bool cameraLock;
  void unloadRenderer();
  void initRenderer(Bounds bound);
  void drawGame(const Thing* things);
};

namespace Update {
  extern float speed;
  extern float seperation_dist;
  extern float seperation_scaling;
  extern float flock_dist;
  extern float alignment_scaling;
  extern float cohesion_scaling;
  extern Thing things[];

  void initGame(Bounds bound);
  void updateGame();
}

namespace Utils { 
  void printVec3(Vector3 vec);
};

namespace Gui { 
  void DrawSliders();
}
