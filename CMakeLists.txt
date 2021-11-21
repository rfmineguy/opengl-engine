cmake_minimum_required(VERSION 3.20)
project (opengl)

find_package(glm REQUIRED)
#find_package(freetype REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})


add_compile_options(
    #tells you if a redundant move operation occurred
    -Wno-redundant-move
    )

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
    
    src/test/test.cpp
    src/test/testClearColor.cpp
    src/test/testTriangle.cpp
    src/test/testShaderDev.cpp
    src/test/testGame.cpp
    
    src/game_object/gameObject.cpp

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

#make spdlog not fetched as i need to edit it a little bit
#FetchContent_Declare(
#    spdlog
#    GIT_REPOSITORY https://github.com/gabime/spdlog
#)
#FetchContent_MakeAvailable(spdlog)
set(SPDLOG_BUILD_EXAMPLES OFF)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/stb)
add_subdirectory(vendor/spdlog)

include_directories(opengl vendor vendor/glm/glm)

add_executable(opengl ${SOURCES})

target_link_libraries(opengl 
    glad glfw imgui glm stb EnTT::EnTT spdlog::spdlog
)
