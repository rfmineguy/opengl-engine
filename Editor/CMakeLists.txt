cmake_minimum_required(VERSION 3.22.1)

project (FireflyEditor LANGUAGES CXX C)

#custom cmake options
option (GEN_APP_BUNDLE "APP_BUNDLE" OFF)

#general cmake setting configuration
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXPORT_COMPILE_COMMANDS True)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#cmake apple build configuration
if (APPLE AND GEN_APP_BUNDLE)
    set (CMAKE_MACOSX_BUNDLE TRUE)
    message ("building for macos")
endif()

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

if (GEN_APP_BUNDLE)
    message ("Building app bundle")
    set (MACOSX_BUNDLE_BUNDLE_NAME "FireflyEditorApp")
    set (MACOSX_BUNDLE_BUNDLE_VERSION "0.1")
    set (ICON_FILE "${PROJECT_SOURCE_DIR}/firefly_engine_logo_vector.icns")

    add_executable(FireflyEditor MACOSX_BUNDLE ${SOURCES} res)
    set_target_properties(FireflyEditor PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.FireflyEditorApp
        MACOSX_BUNDLE_SHORT_VERSION_STRIN "0.1"
        MACOSX_BUNDLE_RESOURCES "firefly_engine_logo_vector.icns"
        MACOSX_BUNDLE_ICON_FILE "firefly_engine_logo_vector.icns"
        )
    file (COPY ${ICON_FILE} DESTINATION FireflyEditor.app/Contents/Resources)
    file (COPY res DESTINATION FireflyEditor.app/Contents/Resources)
    file (COPY imgui.ini DESTINATION FireflyEditor.app/Contents/Resources)

else()
    message ("Building normal executable")
    add_executable(FireflyEditor ${SOURCES})
endif()

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
