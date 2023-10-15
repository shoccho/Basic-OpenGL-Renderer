#pragma once

#include "Test.h"
#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test{
    class TestTexture2D : public Test{
    public:
        TestTexture2D();
        ~TestTexture2D() {}

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        int m_Count;
        std::vector<glm::vec3> m_Translations;
        glm::mat4 m_View, m_Projection;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
    };
}
