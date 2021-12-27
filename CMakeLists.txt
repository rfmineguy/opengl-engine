cmake_minimum_required(VERSION 3.20)
project (opengl LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

add_compile_options(
    #tells you if a redundant move operation occurred (works only with c++)
    -Wno-redundant-move
    )

set(SOURCES 
    src/main.cpp

    src/window/window.cpp

    src/render_data/shader.cpp
    src/render_data/geometry.cpp
    src/render_data/texture.cpp
    src/render_data/textureAtlas.cpp
    
    src/renderer/basicRenderer2d.cpp
    src/renderer/orthoCamera.cpp
    src/renderer/framebuffer.cpp

    src/engine/imguilayer.h
    src/engine/scene.cpp
    
    src/engine/engine.cpp
    src/serializer/serializer.h
    )

set(SPDLOG_BUILD_EXAMPLES OFF)

add_subdirectory(vendor/imgui)
add_subdirectory(vendor/imgui_file_dialog)
add_subdirectory(vendor/stb)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/json)
add_subdirectory(vendor/ImGuizmo)

include_directories(opengl vendor vendor/glm/glm)

add_executable(opengl ${SOURCES})

target_precompile_headers(opengl PUBLIC src/corepch.h)

target_link_libraries(opengl
    glfw 
    imgui 
    imgui_file_dialog
    imguizmo
    glm 
    stb 
    EnTT::EnTT 
    spdlog::spdlog
    nlohmann_json
)
