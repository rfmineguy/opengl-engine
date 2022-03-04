cmake_minimum_required(VERSION 3.20)
project (FireflyCore LANGUAGES CXX C)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

#file (COPY res DESTINATION ${CMAKE_BINARY_DIR})

set (SOURCES
    src/renderer/shader.cpp
    src/renderer/texture.cpp
    src/renderer/textureAtlas.cpp
    src/util/resourceManager.h
    src/renderer/geometry.cpp
    src/renderer/renderer2D_V2.h
    src/renderer/renderer2D_v2.cpp
    src/renderer/renderer2D.h
    src/renderer/orthoCamera.cpp
    src/renderer/framebuffer.cpp

   src/primitives/quad.cpp

    src/util/stringUtil.h
    src/util/geometryUtil.hpp
    src/util/stringUtil.h
    src/util/mathUtil.h
    src/util/fileUtil.h
    src/util/glUtil.h
    src/util/timer.h
    src/util/timer.cpp
    src/util/log.h
    
    src/core/engine/engine.h
    src/core/engine/engine.cpp
    src/core/engine/scene.h
    src/core/engine/scene.cpp

    src/window/window.cpp
    )

set (SPDLOG_BUILD_EXAMPLES OFF)

add_subdirectory (../vendor/stb    "${CMAKE_CURRENT_BINARY_DIR}/stb")
add_subdirectory (../vendor/spdlog "${CMAKE_CURRENT_BINARY_DIR}/spdlog")
add_subdirectory (../vendor/glad   "${CMAKE_CURRENT_BINARY_DIR}/glad")
add_subdirectory (../vendor/glm    "${CMAKE_CURRENT_BINARY_DIR}/glm")
add_subdirectory (../vendor/json   "${CMAKE_CURRENT_BINARY_DIR}/json")
add_subdirectory (../vendor/glfw   "${CMAKE_CURRENT_BINARY_DIR}/glfw")
add_subdirectory (../vendor/entt   "${CMAKE_CURRENT_BINARY_DIR}/entt")

include_directories (FireflyCore
    src/
    ../vendor/
    )
add_library (FireflyCore SHARED ${SOURCES})
target_precompile_headers(FireflyCore PUBLIC src/core/corepch.h)

install (TARGETS FireflyCore DESTINATION usr/lib)

target_link_libraries (FireflyCore
    glad
    glfw
    glm
    stb
    EnTT::EnTT
    spdlog::spdlog
    nlohmann_json
    )
