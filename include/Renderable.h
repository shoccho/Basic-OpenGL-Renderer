#pragma once

#include "Node.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <memory>

class Renderable : public Node {
public:
    Renderable(std::vector<Vertex> vertices, std::vector<unsigned int> indecies,
               VertexBufferLayout layout,
               const std::string shader, const std::string texture);

    ~Renderable();

    void OnUpdate(float deltaTime) override;

    void OnRender() override;

    void OnImGuiRender() override;

    void UpdateBuffer(std::vector<Vertex> nBuffer);

private:
    glm::vec3 m_Translation;
    std::vector<Vertex> m_VBuffer;
    std::vector<unsigned int> m_Indices;
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texture;
    std::unique_ptr<VertexBufferLayout> m_Layout;
};

