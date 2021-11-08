#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../window/inputData.h"

const float DEFAULT_YAW = -90.f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_SPEED = 2.5f;
const float DEFAULT_SENSITIVITY = 0.1f;
const float DEFAULT_ZOOM = 45.0f;

class PerspectiveCamera {
public:
    PerspectiveCamera();
    ~PerspectiveCamera();
    glm::mat4 GetView();
    glm::mat4 GetProj();
    glm::vec3 GetPos();
    glm::vec3 GetFront();
    void Movement(float dt);
    void UpdateProj(int width, int height);

public:
    float yaw, pitch;
    float zoom;

private:
    float moveSpeed;
    float mouseSensitivity;
    glm::vec3 camPos, camTarget, camDirection;
    glm::vec3 camUp, camFront, camRight;
    glm::vec3 worldUp;

private:
    int mWidth, mHeight;
    glm::mat4 view, projection;

private:
    void UpdateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        camRight = glm::normalize(glm::cross(camFront, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        camUp    = glm::normalize(glm::cross(camRight, camFront));
    }
};
