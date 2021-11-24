# Feijoa

![Feijoa Logo](/Resources/Branding/Feijoa_Logo.png?raw=true "Feijoa")

Feijoa is primarily an early-stage interactive application and rendering engine for **Windows**. Currently not much is implemented.

***

## Getting Started
Visual Studio 2017 or 2019 is recommended, Feijoa is officially untested on other development enviroments, for now i m focused on Windows build only.

<ins>**1. Cloning this repository:**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/Htrap19/Feijoa.git`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the nessesary submodules.

<ins>**2. Configuring project for Visual Studio:**</ins>

After cloning execute the [Win-GenProjects.bat](https://github.com/Htrap19/Feijoa/blob/main/scripts/Win-GenProject.bat) script, which will then generate a Visual Studio solution file.

If changes are made, or if you want to regenerate project files, rerun the [Win-GenProjects.bat](https://github.com/Htrap19/Feijoa/blob/main/scripts/Win-GenProject.bat) script file found in `scripts` folder.

***

## The Plan
The plan for Feijoa is to create a powerfull 3D engine.

### Main branches:

- `main` This branch have only 2D renderer stuff, inspired from [TheCherno/Hazel](https://github.com/TheCherno/Hazel)
- `dev`  This branch have advanced 3D renderer and more like ([Assimp](https://github.com/Htrap19/Feijoa-Assimp), Batch rendering, Particle system, etc...)

### Features to come:
- Fast 2D renderer (UI, particles, sprites, etc...)
- High-fidelity Physically-Based 3D rendering
- Support for Mac, Linux, Android and iOS
- Native rendering API support (DirectX, Vulkan, Metal)
- Fully featured viewer and editor applications
- Fully scripted interaction and behavior
- Integrated 2D and 3D physics engine
- Procedural terrain and world generation
