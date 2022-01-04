# About
My Website : https://rfmineguy.github.io/rfmineguy-website/

=======
This README is does not fully document the engine, and there is no proper documentation generated for it. I don't recommend using this for anything serious for multiple reasons.<br> The main one being that it is no where close to being in a fully stable state, and doesn't have a runtime.

# Firefly Engine

Firefly Engine is a personal project for me that was intended to be a small introduction to both opengl and c++. It ended up becomming something much more than that as I was just having to much fun developing it and learning new concepts of c++ to stop! So I created a trello board as a roadmap, and it very quickly grew in size and ambition, which is a good thing considering this is a learning project! There were many basic things in c++ that I didn't know how to do at the start of the project. The main one being understanding the c++ linker, and using libraries to aid my development.

## Features
 - A basic 2D renderer
 - A resource management system
   * split into engine resources and project resources
 - A basic scene system (WIP)
=======
 - Json serialization
 - A fairly robust editor ui
   * Resources
   * Scene Heirarchy (WIP)
   * Properties
   * File Browser
   * Signals (WIP, planned)
 - Projects
   * User specified project directory
   * Interface for creating/opening projects (not fully implemented)

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

## Build Instructions (There are no precompiled binaries at the moment, but they are planned)
 1. git clone https://github.com/rfmineguy/opengl-engine
   - To build the **Editor** *cd opengl-engine/Editor/*
   - To build the **Runtime** *cd opengl-engine/Runtime/*
   - To build the **Core** *cd opengl-engine/Core/*
 2. sh build.sh
 3. It will take some time, but will automatically open the application for you when its done building

=======
### Projects
 - WIP

### Json Serializer
 - WIP

## Build Instructions
 1. git clone https://github.com/rfmineguy/opengl-engine into a directory of your choosing
 2. cd opengl-engine
 3. sh build.sh
 
 **Important Information**
 * Be sure to reclone this repo when I update it (versions are NOT guaranteed to be compatible with another version)
   + I don't recommend even doing this given how limited of an application this is in its current state
 * I'll do my best to make sure existing projects remain compatible, but once again there is no guarantee that this will be the case
>>>>>>> 691a5ee8edbfa035634f587a67a5c63e8411f552

## Build Info
 * Tested & working on Linux (Manjaro Arch)
 * Tested & working on MacOs 12.1
 * Untested on Windows
