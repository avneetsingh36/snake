#include "raylib.h"

int main() {
  // Initialization
  InitWindow(800, 600, "Raylib - Basic Window");

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);
    EndDrawing();
  }

  // De-Initialization
  CloseWindow();  // Close window and OpenGL context

  return 0;
}
