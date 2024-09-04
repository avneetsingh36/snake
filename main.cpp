#include <raylib.h>
#include <raymath.h>

#include <deque>
#include <iostream>

Color darkGrey = {51, 51, 51, 255};
Color purple = {205, 193, 255, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  } else {
    return false;
  }
}

class Snake {
 public:
  std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

  Vector2 direction = {1, 0};

  void Draw() {
    for (unsigned int i = 0; i < body.size(); i++) {
      float x = static_cast<float>(body[i].x);
      float y = static_cast<float>(body[i].y);

      Rectangle segment = Rectangle{
          x * static_cast<float>(cellSize), y * static_cast<float>(cellSize),
          static_cast<float>(cellSize), static_cast<float>(cellSize)};

      DrawRectangleRounded(segment, 0.5f, 6, darkGrey);
    }
  }

  void Update() {
    body.pop_back();
    body.push_front(Vector2Add(body[0], direction));
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

class Game
{
public:
    Snake snake = Snake();
    Food food = Food();

    void Draw() {
        snake.Draw();
        food.Draw();
    }

    void Update() {
        snake.Update();
    }
};

int main() {
  std::cout << "Starting the game... " << '\n';

  InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake");
  SetTargetFPS(60);

  Game game = Game();

  while (WindowShouldClose() == false) {
    BeginDrawing();

    if (eventTriggered(0.2)) {
      game.Update();
    }

    if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
      game.snake.direction = {0, -1};
    }

    if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
      game.snake.direction = {0, 1};
    }

    if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
      game.snake.direction = {-1, 0};
    }
    if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
      game.snake.direction = {1, 0};
    }
    // Draw
    ClearBackground(purple);

    game.Draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
