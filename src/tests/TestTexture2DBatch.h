#pragma once

#include "Test.h"
#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test{
    class TestTexture2DBatch : public Test{
    public:
        TestTexture2DBatch();
        ~TestTexture2DBatch(){};

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        int m_Count;
        glm::vec3 m_Translation;
        glm::mat4 m_View, m_Projection;
        std::vector<Vertex> m_VBuffer;
        std::vector<unsigned int> m_Indices;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture1;
        std::unique_ptr<Texture> m_Texture2;
    };
}
