# Firefly Engine

Firefly Engine is a personal project for me that was intended to be a small introduction to both opengl and c++. It ended up becomming something much more than that as I was just having to much fun developing it and learning new concepts of c++ to stop! So I created a trello board as a roadmap, and it very quickly grew in size and ambition, which is a good thing considering this is a learning project! There were many basic things in c++ that I didn't know how to do at the start of the project. The main one being understanding the c++ linker, and using libraries to aid my development.

## Features
 - A basic 2D renderer
 - A resource management system
   * split into engine resources and project resources
 - A basic scene system (WIP)
 - A fairly robust editor ui
   * Resources
   * Scene Heirarchy (WIP)
   * Properties
   * File Browser
   * Signals (WIP, planned)
 - Projects
   * User specified project directory
   * Interface for creating/opening projects WIP

## Usage
### Resource Manager
 - The resource manager handles Texture, TextureAtlas, and Shader
```c++
 //Load a Texture relative to your project root directory
 ResourceManager::LoadProjectResource<Texture>("test", "textures/test.png");
 
 //Retrieve this loaded Texture
 Texture* t = ResourceManager::GetProjectResource<Texture>("test");
```

### Scene System
 - At the moment the engine only ever hosts a single scene, and is located in the __EngineData__ Singleton
 ```c++
  //Create entity
  EngineData::CurrentScene().CreateEntity("entityId");
  Entity* e = EngineData::CurrentScene().FindEntity("entityId");
 ```



### Projects

## Build Instructions
 1. git clone https://github.com/rfmineguy/opengl-engine
 2. cd opengl-engine
 3. sh build.sh

## Build Info
 * Tested & working on Linux (Manjaro Arch)
 * Tested & working on MacOs 12.1
 * Untested on Windows
