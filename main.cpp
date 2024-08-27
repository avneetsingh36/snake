#include <raylib.h>

#include <deque>
#include <iostream>

Color darkGrey = {51, 51, 51, 255};
Color purple = {205, 193, 255, 255};

int cellSize = 30;
int cellCount = 25;

class Snake {
 public:
  std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

  void Draw() {
    for (int i = 0; i < body.size(); i++) {
      int x = body[i].x;
      int y = body[i].y;
      DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, darkGrey);
    }
  }
};

class Food {
 public:
  Vector2 position;
  Texture2D texture;

  Food() {
    Image image = LoadImage("graphic/food.png");
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
  Snake snake = Snake();

  while (WindowShouldClose() == false) {
    BeginDrawing();

    // Draw
    ClearBackground(purple);

    food.Draw();
    snake.Draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
