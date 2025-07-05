#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;
const float zoomSpeed = 1.01f;
const float offsetSpeedMul = 2.0f;
const float startingZoom = 0.75f;

int main(void) {
  InitWindow(screenWidth, screenHeight, "mandelbrot sets");

  Shader shader = LoadShader(0, "mandelbrot.fs");

  RenderTexture2D target =
      LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

  float offset[2] = {0.0f, 0.0f};
  float zoom = startingZoom;

  int zoomLoc = GetShaderLocation(shader, "zoom");
  int offsetLoc = GetShaderLocation(shader, "offset");

  SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);

  bool showControls = false;

  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    // Handle zooming and panning
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) ||
        IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      zoom *=
          IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? zoomSpeed : 1.0f / zoomSpeed;

      Vector2 mousePos = GetMousePosition();
      Vector2 offsetVelocity = {
          (mousePos.x / (float)screenWidth - 0.5f) * offsetSpeedMul / zoom,
          (mousePos.y / (float)screenHeight - 0.5f) * offsetSpeedMul / zoom};

      offset[0] += GetFrameTime() * offsetVelocity.x;
      offset[1] += GetFrameTime() * offsetVelocity.y;

      SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
      SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);
    }

    if (IsKeyPressed(KEY_R)) {
      zoom = startingZoom;
      offset[0] = 0.0f;
      offset[1] = 0.0f;
      SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
      SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);
    }

    if (IsKeyPressed(KEY_F1))
      showControls = !showControls;

    // Render Mandelbrot set to texture
    BeginTextureMode(target);
    ClearBackground(BLACK);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    BeginShaderMode(shader);
    DrawTextureEx(target.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, WHITE);
    EndShaderMode();

    if (showControls) {
      DrawText("Mouse LEFT/RIGHT = Zoom In/Out", 10, 15, 10, RAYWHITE);
      DrawText("Move mouse while zooming to pan", 10, 30, 10, RAYWHITE);
      DrawText("Press R to reset view", 10, 45, 10, RAYWHITE);
      DrawText("Press F1 to toggle help", 10, 60, 10, RAYWHITE);
    }
    EndDrawing();
  }

  UnloadShader(shader);
  UnloadRenderTexture(target);
  CloseWindow();

  return 0;
}
