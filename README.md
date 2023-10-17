# Basic-OpenGL-Renderer 🚧 ( Under development 🛠 )

## ⚠️  This is a POC project, so this is not actually usable as a rendering library or game engine of sort

I hope to make this a bit more usable to learn more about openGL and shaders and overall graphics programming.

### Todo:

  - [X] Create a basic openGL Renderer
  
  - [X] Add support for batch rendering
    
  - [ ] Making a renderable entity class ( this can be huge and need to decide how much granular it will be )
  
  - [ ] fix memory leak in batch renderer
  
  - [ ] add camera controls
        
  - [ ] configurable prespective?
      
  - [ ] 3D thingies?
  
  - [ ] make the whole thing a lib 


### Current state:
  - Can draw textured elements
  - Supports batch rendering ( not in a sense that you can just create a bunch of elements and it'll render them in batch, just that you can utilize batch rending using openGL using this renderer )
  - there is a memory leak in batch rendering test
  - Runs on Linux and MacOs with cmake being the only dependencie. can run on windows by changing a lib but opengl support in vms are really bad it seems
    
#### Screenshot

<img width="1072" alt="Screenshot 2023-10-18 at 4 06 38 AM" src="https://github.com/shoccho/Basic-OpenGL-Renderer/assets/33720947/ce6d109b-4559-47b4-a1aa-efdd4ad1c86f">
Rendering 100,000 quads with textures and animated colors at 30+fps on a macbook pro with m1 pro chip

    
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

    
