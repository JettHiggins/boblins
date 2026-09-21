#include "modules.h"

#include <random>

Thing Update::things[MAX_THINGS] = { 0 };

std::random_device rd;
std::mt19937 mt (rd());
std::uniform_real_distribution<float> dist (-1.0, 1.0);

Vector2 lookRotation = { 0 };
Vector2 sensitivity = { 1.0f, 1.0f };

float speed = 0.1f;

Bounds bounds;

void Update::initGame(Bounds bound){
  bounds = bound;
  for (int i{1}; i < MAX_THINGS; ++i){
    things[i].type = CUBE;
    things[i].direction = Vector3Normalize({ dist(mt), dist(mt), dist(mt) });
    //things[i].velocity = dist(mt) * 100;
    Utils::printVec3(things[i].direction);
  }
}

void Update::updateGame(){
  float dt = GetFrameTime();
  for (int i{1}; i < MAX_THINGS; ++i){
    Vector3& p = things[i].position;
    if (p.x < bounds.min.x){
      p.x = bounds.max.x;
    }
    if (p.x > bounds.max.x){
      p.x = bounds.min.x;
    }
    if (p.y < bounds.min.y){
      p.y = bounds.max.y;
    }
    if (p.y > bounds.max.y){
      p.y = bounds.min.y;
    }
    if (p.z < bounds.min.z){
      p.z = bounds.max.z;
    }
    if (p.z > bounds.max.z){
      p.z = bounds.min.z;
    }

    p += things[i].direction * things[i].velocity * dt * speed;
  }
}
