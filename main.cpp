#include <raylib.h>
#include <raymath.h>

#include <deque>
#include <iostream>

Color darkGrey = {51, 51, 51, 255};
Color purple = {205, 193, 255, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque) {
  for (unsigned int i = 0; i < deque.size(); i++) {
    if (Vector2Equals(deque[i], element)) {
      return true;
    }
  }

  return false;
}

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

  bool addSegment = false;

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
    if (addSegment == true) {
      body.push_front(Vector2Add(body[0], direction));
      addSegment = false;
    } else {
      body.pop_back();
      body.push_front(Vector2Add(body[0], direction));
    }
  }

  void Reset() {
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
  }
};

class Food {
 public:
  Vector2 position;
  Texture2D texture;

  Food(std::deque<Vector2> snakeBody) {
    Image image = LoadImage("graphic/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos(snakeBody);
  }

  ~Food() { UnloadTexture(texture); }

  void Draw() {
    DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
  }

  Vector2 GenerateRandomCell() {
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return Vector2{x, y};
  }

  Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody) {
    Vector2 position = GenerateRandomCell();
    while (ElementInDeque(position, snakeBody)) {
      position = GenerateRandomCell();
    }

    return position;
  }
};

class Game {
 public:
  Snake snake = Snake();
  Food food = Food(snake.body);
  bool running = true;

  void Draw() {
    snake.Draw();
    food.Draw();
  }

  void Update() {
    if (running) {
      CheckCollisionsWithFood();
      CheckCollisionsWithEdges();
      CheckCollisionsWithHead();
      snake.Update();
    }
  }

  void CheckCollisionsWithFood() {
    if (Vector2Equals(snake.body[0], food.position)) {
      snake.addSegment = true;

      food.position = food.GenerateRandomPos(snake.body);
    }
  }

  void CheckCollisionsWithEdges() {
    if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
      GameOver();
    }
    if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
      GameOver();
    }
  }

  void CheckCollisionsWithHead() {
    std::deque<Vector2> headlessBody = snake.body;
    Vector2 head = headlessBody[0];
    headlessBody.pop_front();

    for (int i = 0; i < headlessBody.size(); i++) {
      if (Vector2Equals(head, headlessBody[i])) {
        GameOver();
      }
    }
  }

  void GameOver() {
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
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
      game.running = true;
    }

    if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
      game.snake.direction = {0, 1};
      game.running = true;
    }

    if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
      game.snake.direction = {-1, 0};
      game.running = true;
    }
    if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
      game.snake.direction = {1, 0};
      game.running = true;
    }
    // Draw
    ClearBackground(purple);

    game.Draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
