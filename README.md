
# Pong Game with Audio Manager

A classic Pong game built using C++ and SFML. This project includes game mechanics such as ball movement, paddle control, scoring, and sound effects for a more immersive gaming experience. 

## Setup & Installation

### Prerequisites

Make sure you have the following installed:

- **C++ Compiler** (e.g., GCC, Clang)
- **SFML** (Simple and Fast Multimedia Library) – You can install SFML by following [this guide](https://www.sfml-dev.org/download.php).
- **CMake** – For easy building of the project.

### Clone the Repository

```bash
git clone https://github.com/yourusername/pong-game.git
cd pong-game
```

### Building the Project

1. Create a build directory:

```bash
mkdir build
cd build
```

2. Run `CMake` to generate the build files:

```bash
cmake ..
```

3. Build the project using your preferred C++ compiler (e.g., `make`):

```bash
make
```

4. Run the executable:

```bash
./pong-game
```

### Running the Game

Once the game is compiled and running, control your paddle with the following keys:

- **W** to move up.
- **S** to move down.
- **Arrow Up** to move the opponent's paddle up.
- **Arrow Down** to move the opponent's paddle down.

The game will play until a predetermined score limit is reached.

## Audio Manager (TODO)

The **Audio Manager** is responsible for playing sound effects and music throughout the game. It includes functions to load, play, and stop sounds, making it easy to integrate new audio assets.

### How It Works

1. **Load Sound Effects**: Sounds are loaded from files and assigned to keys like `"hit_paddle"`, `"score"`, etc.
2. **Play Sounds**: When events occur (e.g., ball hitting a paddle or scoring), the corresponding sound is played.
3. **Background Music**: You can load and play background music which loops until stopped.

### Example Usage

In the `GameManager`, you can play sounds like so:

```cpp
void GameManager::onBallCollision() {
    audioManager.playSound("hit_paddle");
}

void GameManager::scoreCallback(int player) {
    audioManager.playSound("score");
    audioManager.playMusic("bg_music");  // Start background music
}
```

### Audio File Format

- **Sound Effects**: WAV or MP3
- **Background Music**: OGG or MP3

Make sure your audio files are placed in the `assets/sounds/` and `assets/music/` directories.

## Contributing

Feel free to fork this project, make changes, and submit pull requests. If you have any suggestions, feel free to open an issue!

### Things to improve

- Add more sound effects (e.g., ball bouncing off the walls).
- Add visual effects, such as particle trails behind the ball at higher speeds.
- Multiplayer support with network play.

## License

This project is open-source and available under the MIT License. See the [LICENSE](LICENSE) file for more information.

---

Happy coding, and enjoy your Pong game with immersive audio effects!
