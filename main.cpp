#include <raylib.h>

#include <iostream>

Color darkPurple = {165, 148, 249, 255};
Color purple = {205, 193, 255, 255};

int cellSize = 30;
int cellCount = 25;

class Food {
 public:
  Vector2 position;
  Texture2D texture;

  Food() {
    Image image = LoadImage("graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos();
  }

  ~Food() { UnloadTexture(texture); }

  void Draw() {
    DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
  }

  Vector2 GenerateRandomPos() {
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return Vector2{x, y};
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
