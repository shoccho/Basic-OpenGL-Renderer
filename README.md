# Basic-OpenGL-Renderer 🚧 ( Under development 🛠 )

## ⚠️  This is a POC project, so this is not actually usable as a rendering library or game engine of sort

I hope to make this a bit more usable to learn more about openGL and shaders and overall graphics programming.


### Current state:
  - this project only renders a rectangle (see the screenshot) but you can modify the verticies and shaders to draw anything you want.
  - Runs on Linux and MacOs with cmake being the only dependencie.
    
#### Screenshot
<img width="752" alt="Screenshot 2023-10-09 at 4 58 22 PM" src="https://github.com/shoccho/Basic-OpenGL-Renderer/assets/33720947/22449f9f-baa3-49b4-8c17-665d0b55fca2">

    
### Requirements:
  - gcc or clang (not tested with msvc or tcc or other c compilers)
  - cmake 

### Build instructions:

  - First clone the Repo
    ```shell
      git clone --recurse-submodules https://github.com/shoccho/Basic-OpenGL-Renderer
    ```
    
  - Then cd into the repo and create a build directory
    ```
      mkdir build  && cd build
    ```
    
  - Then run
    ```
      cmake ..
      make
    ```
  - Now you can execute the program using
    ```
      ./main
    ```
or if you use any cmake supported ide( CLion, KDevelop, QtCreator, Vim (via a plugin), Visual Studio, VS code (plugin)) to open the project and run it from there

or you can use cmake to [generate project files](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#ide-build-tool-generators)  for other ides as well like xcode or code:blocks 

    
