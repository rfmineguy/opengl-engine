#include "perspectiveCamera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>


PerspectiveCamera::PerspectiveCamera() 
:camPos(0, 0, -5), camFront(0, 0, -1), worldUp(0.0f, 1.0f, 0.0f){
    yaw = DEFAULT_YAW;
    pitch = DEFAULT_PITCH;
    moveSpeed = DEFAULT_SPEED;
    mouseSensitivity = DEFAULT_SENSITIVITY;
    zoom = DEFAULT_ZOOM;
    UpdateProj(600, 600);
}

PerspectiveCamera::~PerspectiveCamera() {
}

glm::mat4 PerspectiveCamera::GetView() {
    view = glm::lookAt(camPos, camPos + camFront, camUp);
    return view;
}

glm::mat4 PerspectiveCamera::GetProj() {
    projection = glm::perspective(glm::radians(zoom), (float) mWidth / (float) mHeight, 0.1f, 100.0f);
    return projection;
}

glm::vec3 PerspectiveCamera::GetPos() {
    return camPos;
}

glm::vec3 PerspectiveCamera::GetFront() {
    return camFront;
}

void PerspectiveCamera::Movement(float dt) {
    //keyboard movement
    float velocity = moveSpeed * dt;
    if (!Input.mouseCaptured) 
        return;

    if (Input.keys[GLFW_KEY_W]) {
        camPos += camFront * velocity;
    }
    if (Input.keys[GLFW_KEY_S]) {
        camPos -= camFront * velocity;
    }
    if (Input.keys[GLFW_KEY_A]) {
        camPos -= camRight * velocity;
    }
    if (Input.keys[GLFW_KEY_D]) {
        camPos += camRight * velocity;
    }

    //mouse movement
    Input.mouseOffsetX *= mouseSensitivity;
    Input.mouseOffsetY *= mouseSensitivity;

    yaw += Input.mouseOffsetX;
    pitch -= Input.mouseOffsetY;

    if (yaw > 360.0f)
        yaw = 0.0f;
    if (yaw < 0.0f)
        yaw = 360.0f;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    //mouse scrolling
    zoom -= Input.scrollYOffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
    
    UpdateCameraVectors();
}

void PerspectiveCamera::UpdateProj(int width, int height) {
    mWidth = width;
    mHeight = height;
    std::cout << "UpdateProj" << std::endl;
}
