#include "orthoCamera.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>
#include "../window/inputData.h"

#include "../corepch.h"
OrthoCamera::OrthoCamera()
:mWidth(600), mHeight(600){
    SetPos(glm::vec3(0.0f, 0.0f, 0.0f));

    projection = glm::ortho(0.0f, static_cast<float>(mWidth), 0.0f, static_cast<float>(mHeight), -1.0f, 1.0f);
    view = glm::mat4(1.0);
    viewProjection = projection * view;
    camRotation = 0.0f;
}

OrthoCamera::~OrthoCamera() {

}

void OrthoCamera::Movement() {
    if (Input.keys[GLFW_KEY_W])
        DeltaPos(0, -1);
    if (Input.keys[GLFW_KEY_S])
        DeltaPos(0, 1);
    if (Input.keys[GLFW_KEY_A])
        DeltaPos(-1, 0);
    if (Input.keys[GLFW_KEY_D])
        DeltaPos(1, 0);
    /*
    if (Input.keys[GLFW_KEY_LEFT])
        DeltaRot(-0.01f);
    if (Input.keys[GLFW_KEY_RIGHT])
        DeltaRot(0.01f);
    */
}

void OrthoCamera::UpdateProj(int width, int height) {
    mWidth = width;
    mHeight = height;
    projection = glm::ortho(0.0f, static_cast<float>(mWidth), 0.0f, static_cast<float>(mHeight), -1.0f, 1.0f);
}

void OrthoCamera::RecalculateView() {
    //LOG_DEBUG("{}", camRotation);
    glm::mat4 transform = glm::translate(glm::mat4(1.0), camPos);
    transform = glm::rotate(transform, camRotation, glm::vec3(0, 0, 1));
    view = glm::inverse(transform);
    viewProjection = projection * view;
}
