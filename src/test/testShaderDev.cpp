#include "testShaderDev.h"
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include "../util/geometryUtil.hpp"
#include "../window/inputData.h"
#include "../window/windowData.h"
#include <cmath>
#include "../util/mathUtil.h"

namespace test {
    TestShaderDev::TestShaderDev() {
        camera.SetPos({-WinData.windowWidth / 2.f, -WinData.windowHeight / 2.f, 0.0f});

        //transforms.resize(0);
        int width=10, height=10;
        for (int i = 0; i < 100; i++) {
            int x = i % width;
            int y = i / width;
            /*
            Transform t = {};
            t.SetPos(x * 64, y * 64);
            t.SetRot(i);
            t.SetScale(48);
            renderer.AddTransform(t);
            */
        }
    }

    TestShaderDev::~TestShaderDev() {
    }

    void TestShaderDev::Update(float dt) {
        time = glfwGetTime();
        camera.Movement();
        /*
        renderer.GetShader().Bind();
        renderer.GetShader().Set4fv("view", camera.GetView());
        renderer.GetShader().Set4fv("projection", camera.GetProj());
        for (int i = 0; i < transforms.size(); i++) {
            transforms[i].DeltaRot(1); //Random::RandFloatRange(-1.0f, 1.0f));
        }
        */
    }

    void TestShaderDev::Resize(int width, int height) {
        camera.UpdateProj(width, height);
    }

    void TestShaderDev::Render() {
        glClearColor(0.4f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //renderer.Draw();
        //batch.Begin(false);
        //batch.Add(quad1);
        //batch.Add(quad2);
        //batch.Flush();
    }

    void TestShaderDev::ImGuiRender() {
        ImGui::Text("Cursor captured %d", Input.mouseCaptured);
        ImGui::Text("Cursor offset %d", Input.mouseOffsetY);
        
        vec3 camPos = camera.GetPos();
        ImGui::Text("Cam pos {%0.4f, %0.4f}", camPos.x, camPos.y); 
    
        //ImGui::Text("Draw call count {%d}", renderer.drawCalls);
        ImGui::Text("FPS %0.4f", WinData.fps);
        ImGui::Text("SPF %0.4f", WinData.spf);
    }
}
