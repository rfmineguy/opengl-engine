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
};

extern InputData Input;
