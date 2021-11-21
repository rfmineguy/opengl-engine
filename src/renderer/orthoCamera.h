#pragma once
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../util/mathUtil.h"

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
   

    //HomelikeBrick42 helped immensly with this function
    glm::vec2 ScreenToWorld(glm::vec2 mouseCoord) {
        glm::vec2 deviceCoord;
        deviceCoord.x = mouseCoord.x / mWidth * 2.0f - 1;
        deviceCoord.y = (mHeight - mouseCoord.y) / mHeight * 2.0f - 1;

        glm::mat4 projView = glm::inverse(projection * view);
        glm::vec4 translated = projView * glm::vec4(deviceCoord, 1, 1);
        return glm::vec2(translated.x, translated.y) / translated.w; 
    }

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
