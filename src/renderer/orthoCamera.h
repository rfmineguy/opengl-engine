#pragma once
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrthoCamera {
public:
    OrthoCamera();
    ~OrthoCamera();
    void Movement();
    const glm::mat4 GetView() const { return view; }
    const glm::mat4 GetProj() const { return projection; }
    
    void SetPos(glm::vec3 pos) { camPos = pos; RecalculateView(); }
    void DeltaPos(float dx, float dy) { camPos += glm::vec3(dx, dy, 0); RecalculateView(); }
    glm::vec3 GetPos() { return camPos; }

    void SetRotation(float rotation) { camRotation = rotation; RecalculateView(); }
    void DeltaRot(float rotation) { camRotation += rotation; RecalculateView(); }
    float GetRotation() { return camRotation; }

    void UpdateProj(int width, int height);

private:
    void RecalculateView();
private:
    int mWidth, mHeight;

private:
    glm::vec3 camPos;
    float camRotation;

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewProjection;
};
