#include "modules.h"

#include <random>
#include <raymath.h>

Thing Update::things[MAX_THINGS] = { 0 };

std::random_device rd;
std::mt19937 mt (rd());
std::uniform_real_distribution<float> dist (-1.0, 1.0);

Vector2 lookRotation = { 0 };
Vector2 sensitivity = { 1.0f, 1.0f };


Bounds bounds = { 0 };

// Boid controls
float Update::speed = 0.1f;
float Update::seperation_dist = 1.0f;
float Update::seperation_scaling = 5.0f;
float Update::flock_dist = 2.0F; 
float Update::alignment_scaling = 1.0f;
float Update::cohesion_scaling = 1.0f;

void Update::initGame(Bounds bound){
  bounds = bound;
  for (int i{1}; i < MAX_THINGS; ++i){
    things[i].type = CUBE;
    things[i].direction = Vector3Normalize({ dist(mt), dist(mt), dist(mt) });
    //things[i].velocity = dist(mt) * 100;
    Utils::printVec3(things[i].direction);
  }
}

void update_input(){
  if (IsKeyPressed(KEY_BACKSPACE)){
    printf("Locked\n");
    if (Renderer::cameraLock){
      EnableCursor();
    } else {
      DisableCursor();
    }
    Renderer::cameraLock = !Renderer::cameraLock;
  }
}

void Update::updateGame(){
  update_input();
  float dt = GetFrameTime();
  for (int i{1}; i < MAX_THINGS; ++i){
    // Bounds check
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

    // Boids checks
    Vector3 alignment = { 0 };
    Vector3 cohesion = { 0 };
    size_t flockmates = 0;
    for (int j{1}; j < MAX_THINGS; ++j){
      
      if (i == j){
        continue;
      }

      //Steer away check
      if (CheckCollisionSpheres(p, seperation_dist, things[j].position, 1.0f)){
        Vector3 seperation = p - things[j].position;
        things[i].direction += Vector3Normalize(seperation) * seperation_scaling * dt;
      }
      //Flockmates count
      if (CheckCollisionSpheres(p, flock_dist, things[j].position, 1.0f)){
        alignment += things[j].direction;
        cohesion += things[j].position;
        flockmates++;
      }
    }

    if (flockmates > 0){
      alignment /= flockmates;
      cohesion /= flockmates;

      things[i].direction += Vector3Normalize(alignment) * alignment_scaling * dt;
      things[i].direction += Vector3Normalize(cohesion - p) * cohesion_scaling * dt;

      things[i].direction = Vector3Normalize(things[i].direction);

    }

    p += things[i].direction * things[i].velocity * dt * speed;
  }
}
