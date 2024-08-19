#include <raylib.h>

#include <iostream>

Color darkPurple = {165, 148, 249, 255};
Color purple = {205, 193, 255, 255};

int cellSize = 30;
int cellCount = 25;

class Food {
 public:
  Vector2 position = {5, 6};

  void Draw() {
    DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize,
                  cellSize, darkPurple);
  }
};

int main() {
  std::cout << "Starting the game... " << '\n';

  InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake");
  SetTargetFPS(60);
  Food food = Food();

  while (WindowShouldClose() == false) {
    BeginDrawing();

    // Draw
    ClearBackground(purple);

    food.Draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
