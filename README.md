# Lightning Snake Game

Experience a fast-paced twist on the classic Snake Game, built using modern C++20 standards and the **Raylib** graphics library. This implementation focuses on delivering a smooth and responsive gameplay experience with enhanced speed and intuitive controls. Perfect for players looking for a quick, engaging challenge.


<img src="./assets/screenshot.png" alt="Snake Game Screenshot" width="600"/>

## How to Play
- **Movement**: Use the arrow keys to move the snake up, down, left, or right.
- **Objective**: Eat food to grow and increase your score.
- **Game Over**: The game ends if the snake collides with itself or the boundaries of the screen.

## Features
- **Snake Movement**: The snake moves across a grid, growing with each food consumed.
- **Random Food Placement**: Food is generated in random positions, avoiding overlap with the snake's body.
- **Score Tracking**: Your score increases as you eat food.
- **Collision Detection**: The game checks for collisions with food, edges, and the snake's own body.

## Controls
- **Up Arrow**: Move up
- **Down Arrow**: Move down
- **Left Arrow**: Move left
- **Right Arrow**: Move right

## Installation

To compile and run the game, follow these steps:

##### Install Raylib:
```brew install raylib ```

##### Compile the game (for mac - make sure to use the equivalent if on other operating systems):
```g++ -std=c++20 -o main main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo ```

##### Run the game:
```./main```

Alternatively, you can use the precompiled executable available in the repository. Just download it and run: ```.\snake_game_executable```


## Project Structure

- `main.cpp`: Contains the entire game logic including the snake movement, food generation, and game state handling.
- `raylib_HW.cpp`: A starter file to ensure that your Raylib setup is working correctly. It's a basic "Hello World" style program for testing graphics.
- `snake_game_executable`: The precompiled executable file to run the game directly.
- `README.md`: The project's README file containing instructions and documentation.
- `assets/`: Contains game assets like images and textures.
  - `screenshot.png`: Screenshot of the game.
- `graphic/`: Stores graphic resources.
  - `food.png`: Image used for food in the game.


## License
This project is licensed under the MIT License.
