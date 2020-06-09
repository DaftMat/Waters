# Waters !
A minimal rendering engine for waters (and terrains)

## List of dependencies:
 - Here's the list of repos you want to install before running this app.
   - [GLFW](https://github.com/glfw/glfw)
   - [GLM](https://github.com/g-truc/glm)
   - [Assimp](https://github.com/assimp/assimp)
   - [spdlog](https://github.com/gabime/spdlog)
   - [OpenGL/GLSL 4.4+](https://www.opengl.org/)
 - Dependencies as submodules :
   - [GLAD](https://glad.dav1d.de/)
   - [random](https://github.com/effolkronium/random) by effolkronium
   - [STB](https://github.com/nothings/stb)

## Downloading, Compiling & Executing
### Downloading
```txt
$ git clone --recurse-submodules https://github.com/DaftMat/Waters.git
```
### Compiling
From project's root:
```txt
$ mkdir build
$ cd build
$ cmake ..
$ make
```
### Executing
From `bin/Release/` :
```txt 
$ ./waters
```

## Using The Engine
As well, you can inherit from `BaseApplication` and use the engine api you made to build your own windowed abstraction. Follow the guidelines described by this project.
