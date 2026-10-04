#include "modules.h"
#include <raylib.h>
#include <raymath.h>

Camera3D Renderer::camera = { 0 };
bool Renderer::cameraLock = false;

Model model = { 0 };


Matrix transforms[MAX_THINGS] = { 0 };

Shader shader = { 0 };

Vector3 cubePos;
Vector3 size;

void Renderer::unloadRenderer(){
  UnloadShader(shader);
  UnloadModel(model);
}

void Renderer::initRenderer(Bounds bound){
  shader = LoadShader("resources/vertex.glsl", "resources/fragment.glsl");

  shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");

  camera.position = {10.0f, 10.0f, 10.0f};
  camera.fovy = 90.0f;
  camera.target  = {0.0f, 0.0f, 0.0f};
  camera.up = {0, 1.0f, 0};
  camera.projection = CAMERA_PERSPECTIVE;

  model = LoadModel("resources/models/Goblin_Warrior.glb");

  for (int i{0}; i < model.meshCount; ++i){
    Mesh& mesh = model.meshes[i];
    Material& mat = model.materials[model.meshMaterial[i]];
    mat.shader = shader;
    mat.maps[MATERIAL_MAP_DIFFUSE].color = WHITE;
  }

  size = {bound.max - bound.min};
  cubePos = bound.min + (size/2);

}


void Renderer::drawGame(const Thing* things){
  if (cameraLock){
    UpdateCamera(&camera, CAMERA_FREE);
  }
  const Vector3 modelRot {0, 1, 0};
  for (int i {1}; i < MAX_THINGS; ++i){
    const Vector3& direction = things[i].direction;
    //rotation matrix
    float angle = Vector3Angle(direction, modelRot);
    Vector3 axis = Vector3CrossProduct(modelRot, direction);
    Matrix rotation = MatrixRotate(axis, angle);

    //translation matrix
    Vector3 pos = things[i].position;
    Matrix translation = MatrixTranslate(pos.x, pos.y, pos.z);


    transforms[i] = MatrixMultiply(rotation, translation);
  }

  BeginMode3D(camera);
    for (int i{0}; i < model.meshCount; ++i){
      Mesh& mesh = model.meshes[i];
      Material& mat = model.materials[model.meshMaterial[i]];
      DrawMeshInstanced(mesh, mat, &transforms[1], MAX_THINGS - 1);
    }
    // DrawCubeV(cubePos, size, ColorAlpha(SKYBLUE, 0.5f));
  EndMode3D();
  Gui::DrawSliders();
}
