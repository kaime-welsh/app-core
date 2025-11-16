#include "Game.h"
#include "App.h"
#include "raylib.h"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

static Camera3D camera;
static Shader shader;
static Light lights[MAX_LIGHTS];

void GameLayer::OnAttach() {
  auto &registry = Core::App::Get().GetRegistry();

  DisableCursor();

  camera.position = (Vector3){2.0f, 4.0f, 6.0f};
  camera.target = (Vector3){0.0f, 0.5f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  shader =
      LoadShader("Assets/Shaders/lighting.vs", "Assets/Shaders/lighting.fs");
  shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  int ambientLoc = GetShaderLocation(shader, "ambient");
  SetShaderValue(shader, ambientLoc, (float[4]){0.1f, 0.1f, 0.1f, 1.0f},
                 SHADER_UNIFORM_VEC4);

  lights[0] =
      CreateLight(LIGHT_POINT, (Vector3){-2, 1, -2}, Vector3(), YELLOW, shader);
  lights[1] =
      CreateLight(LIGHT_POINT, (Vector3){2, 1, 2}, Vector3(), RED, shader);
  lights[2] =
      CreateLight(LIGHT_POINT, (Vector3){-2, 1, 2}, Vector3(), GREEN, shader);
  lights[3] =
      CreateLight(LIGHT_POINT, (Vector3){2, 1, -2}, Vector3(), BLUE, shader);
}

void GameLayer::OnDetach() { UnloadShader(shader); }

void GameLayer::Update() {
  if (WindowShouldClose()) {
    Core::App::Get().Stop();
    return;
  }

  UpdateCamera(&camera, CAMERA_FIRST_PERSON);

  float cameraPos[3] = {camera.position.x, camera.position.y,
                        camera.position.z};
  SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
                 SHADER_UNIFORM_VEC3);

  for (int i = 0; i < MAX_LIGHTS; i++) {
    UpdateLightValues(shader, lights[i]);
  }
}

void GameLayer::Render() {
  BeginDrawing();
  ClearBackground(BLACK);

  BeginMode3D(camera);

  BeginShaderMode(shader);
  DrawPlane(Vector3(), Vector2(10.0, 10.0), WHITE);
  DrawCube(Vector3(), 2.0, 4.0, 2.0, WHITE);
  EndShaderMode();

  DrawGrid(10, 1.0f);
  EndMode3D();

  DrawFPS(10, 10);
  EndDrawing();
}
