cmake_minimum_required(VERSION 3.20)
project (opengl)

find_package(glm REQUIRED)
#find_package(freetype REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCES 
    src/main.cpp
    src/window/window.cpp
    src/render_data/shader.cpp
    src/render_data/geometry.cpp
    src/render_data/texture.cpp
    src/render_data/textureAtlas.cpp
    src/renderer/batch.cpp
    src/renderer/instancedRenderer.cpp
    src/renderer/basicRenderer2d.cpp
    src/renderer/orthoCamera.cpp
    src/renderer/perspectiveCamera.cpp
    src/test/test.cpp
    src/test/testClearColor.cpp
    src/test/testTriangle.cpp
    src/test/testShaderDev.cpp
    src/test/testGame.cpp
    vendor/glad/glad.c
    )

include (FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt
    )
FetchContent_MakeAvailable(EnTT)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/stb)

include_directories(opengl vendor vendor/glm/glm)

add_executable(opengl ${SOURCES} )

target_link_libraries(
    opengl glad glfw imgui glm stb EnTT::EnTT
)
