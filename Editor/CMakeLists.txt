cmake_minimum_required(VERSION 3.20)

project (FireflyEditor LANGUAGES CXX C)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXPORT_COMPILE_COMMANDS True)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

#file (COPY ../Core/res DESTINATION ${CMAKE_BINARY_DIR})
file (COPY res DESTINATION ${CMAKE_BINARY_DIR})
file (COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR})

set (SOURCES
    src/main.cpp
    src/editorWindow.cpp
    src/editor/editorLayer.cpp
    )

add_subdirectory(../Core "${CMAKE_CURRENT_BINARY_DIR}/Core")
add_subdirectory(../vendor/imgui "${CMAKE_CURRENT_BINARY_DIR}/imgui")
add_subdirectory(../vendor/imgui_file_dialog "${CMAKE_CURRENT_BINARY_DIR}/imgui_file_dialog")
add_subdirectory(../vendor/ImGuizmo "${CMAKE_CURRENT_BINARY_DIR}/ImGuizmo")
add_subdirectory(../vendor/nfd-extended "${CMAKE_CURRENT_BINARY_DIR}/nfd-extended")
include_directories (FireflyEditor
    src/
    ../vendor/
    ../Core/src/
    )

add_executable(FireflyEditor ${SOURCES})

target_link_libraries( FireflyEditor
    FireflyCore
    glad
    glfw
    imgui
    imgui_file_dialog
    imguizmo
    glm
    stb
    EnTT::EnTT
    spdlog::spdlog
    nlohmann_json
    nfd
    )
