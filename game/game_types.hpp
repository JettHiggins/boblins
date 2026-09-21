#include <raylib.h>
#pragma once

const int MAX_THINGS = 1000;

enum particleType { NOTHING, GOBLIN, CUBE };

struct Thing {
  Vector3 position = {0};
  Vector3 direction = {0};
  float velocity = 10;
  particleType type = NOTHING;
};

struct Bounds {
  Vector3 min = {0, 0, 0};
  Vector3 max = {10.0f, 10.0f, 10.0f};
};
