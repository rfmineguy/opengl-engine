#include <glm/glm.hpp>

#pragma once
struct InputData {
    bool keys[300];
    bool buttons[20];
    glm::vec2 mouse;
    int lastMouseX, lastMouseY;
    int mouseOffsetX, mouseOffsetY;
    bool mouseCaptured = false;
    bool mouseDown = false;

    double scrollXOffset, scrollYOffset;

    bool IsMouseDown(int id) {
        return buttons[id];
    }
    bool IsKeyDown(int id) {
        return keys[id];
    }
};

extern InputData Input;
