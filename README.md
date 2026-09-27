# Raylib-CPP Starter Template for VS Code

![Language](https://img.shields.io/badge/language-C%2B%2B-brightgreen)
![Raylib](https://img.shields.io/badge/raylib-6.0-00d4aa)
![Platform](https://img.shields.io/badge/platform-Windows%2010%20%7C%2011-blue)
![Editor](https://img.shields.io/badge/editor-VS%20Code-007ACC)

A minimal C++ project scaffold for Visual Studio Code on Windows — includes a bouncing ball demo and zero boilerplate friction.

<p align="center">
  <a href="https://youtu.be/acvgbKRaxDI">
    <img src="preview.jpg" alt="Preview of the bouncing ball demo — click to watch tutorial" width="800">
  </a>
</p>

<p align="center">
  <a href="https://youtu.be/acvgbKRaxDI">
    <img src="https://img.shields.io/badge/▶%20Watch%20the%20Video%20Tutorial-FF0000?style=for-the-badge&logo=youtube&logoColor=white" alt="Watch the Video Tutorial on YouTube">
  </a>
</p>

---

## Get started in 3 steps

**1.** Double-click `main.code-workspace` to open the project in VS Code.

**2.** In the Explorer panel, navigate to the `src/` folder and open `main.cpp`.

**3.** Press `F5` to compile and run.

---

## Building on Linux

The three VS Code configs (task, launch, IntelliSense) each carry per-platform
overrides, so F5 works on Linux as well as Windows. You need `raylib` built and
reachable, plus a C++ toolchain and `gdb`.

**1.** Build and install raylib. The build task passes `DESTDIR=../raylib-install`,
so the expected layout is a `raylib-install` folder **next to** this project:

```bash
git clone --branch 6.0 https://github.com/raysan5/raylib.git raylib-6.0
cd raylib-6.0/src
make PLATFORM=PLATFORM_DESKTOP          # builds ../src/libraylib.a
sudo make install RAYLIB_LIBTYPE=STATIC # or copy manually, see below
```

If you have no root access, `make install` refuses to run — the check is
unconditional, so it fails even when you point it at a custom prefix. Copy the
four files it would have installed by hand:

```bash
PREFIX=../raylib-install
mkdir -p $PREFIX/lib $PREFIX/include
cp raylib-6.0/src/libraylib.a                 $PREFIX/lib/
cp raylib-6.0/src/raylib.h raylib-6.0/src/raymath.h raylib-6.0/src/rlgl.h $PREFIX/include/
```

**2.** If your raylib lives somewhere else, override `DESTDIR` on the command
line rather than editing the task:

```bash
make PROJECT_NAME=main DESTDIR=/path/to/your/prefix
```

Note that a bare `make` with no arguments still looks for raylib under
`/usr/local`, which is raylib's own upstream default, not a bug in this template.

**3.** Open `main.code-workspace` and press `F5`. The `Linux` IntelliSense config
reads headers from `${workspaceFolder}/../raylib-install/include`, so move that
path in `.vscode/c_cpp_properties.json` if you changed `DESTDIR`.

Verified on CachyOS (Arch-based) with GCC 16.2, raylib 6.0 static, GLFW on X11.

---

## What's inside

| | Feature | Details |
|---|---|---|
| 📁 | **Clean folder structure** | All source code lives in `src/` for clear organisation |
| 🎱 | **Bouncing ball demo** | Ready-to-run example using raylib's core 2D drawing API |
| ⚙️ | **VS Code tasks** | Pre-configured build tasks — no manual setup required |
| ✅ | **Tested on Win 10/11** | Works with raylib 6.0 on both platforms out of the box |

---

## Quick look

```cpp
#include <raylib.h>
#include "ball.h"

int main()
{
    const Color darkGreen = {20, 160, 133, 255};

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    Ball ball;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ball.Update();

        BeginDrawing();
            ClearBackground(darkGreen);
            ball.Draw();
        EndDrawing();
    }

    CloseWindow();
}
```

---

## What's changed

The template now uses folders for better organisation. All source code lives in the `src/` folder.

---

## Resources

🎥 [Video Tutorial on YouTube](https://youtu.be/acvgbKRaxDI)
&nbsp;&nbsp;|&nbsp;&nbsp;
📺 [My YouTube Channel](https://www.youtube.com/channel/UC3ivOTE5EgpmF2DHLBmWIWg)
