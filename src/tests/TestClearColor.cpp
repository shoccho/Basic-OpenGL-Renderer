#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui.h"

namespace test {
    TestClearColor::TestClearColor()
        :m_ClearColor{0.2f,0.1f,0.7f, 1.0f}
    {
    }

    void TestClearColor::OnUpdate(float deltaTime) {
    }

    void TestClearColor::OnRender() {

        GL_CALL(glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImGuiRender() {
        ImGui::ColorEdit4("Clear color",m_ClearColor);
    }
}