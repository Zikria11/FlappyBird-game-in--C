# 🐦 Flappy Bird (C++ with Raylib)

A simple clone of the classic **Flappy Bird** built in **C++** using the [Raylib](https://www.raylib.com/) library.  
The goal is simple: fly the bird through the gaps between pillars and survive as long as possible!

---

## 🚀 Features
- Smooth bird physics (gravity + jump control)
- Randomly spawning pillars with gaps
- Increasing difficulty as you play
- Collision detection with game over state
- Minimal, clean code using **Raylib**

---

## 🛠️ Installation & Setup

### On Linux / macOS
```bash
# Install Raylib (if not installed)
sudo apt install libraylib-dev   # Ubuntu / Debian

# OR build from official repo: https://github.com/raysan5/raylib

# Clone this repository
git clone https://github.com/your-username/flappy-bird-raylib.git
cd flappy-bird-raylib

# Compile & run
g++ main.cpp -o flappybird -lraylib -lm -ldl -lpthread -lGL -lX11
./flappybird
```

### On Windows (MSYS2)
``` bash
pacman -S mingw-w64-x86_64-raylib
```
# Clone the repository
``` bash
git clone https://github.com/your-username/flappy-bird-raylib.git
cd flappy-bird-raylib

# Compile & run
g++ main.cpp -o flappybird.exe -lraylib -lopengl32 -lgdi32 -lwinmm
./flappybird.exe
```
📸 Screenshots
<img width="806" height="634" alt="image" src="https://github.com/user-attachments/assets/0ba1e020-0907-4ec7-bf5a-41f74386b453" />






## 📜 License
This project is licensed under the MIT License.
You are free to use, modify, and distribute it.

## 👨‍💻 Author
Zikria Akhtar

GitHub: <link src="www.github.com/Zikria11"></link>

Email: zikriaakhtar08@gmail.com
