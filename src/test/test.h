#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../vendor/imgui/imgui.h"

#include "../util/log.h"

namespace test {
    class Test {
    public:
        Test(){}
        virtual ~Test() {}

        virtual void Update(float dt) {}
        virtual void Render() {}
        virtual void Resize(int width, int height) {}
        virtual void ImGuiRender() {}
    };

    class TestMenu : public Test {
    public:
        TestMenu(Test*& currentTestPointer);

        void ImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name) {
            tests.push_back(std::make_pair(name, []() { return new T(); }));
        }
    private:
        Test*& mCurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> tests;
    };
}
