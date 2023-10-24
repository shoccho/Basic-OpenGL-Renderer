#include "Renderable.h"

#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


Renderable::Renderable(std::vector<Vertex> vertices, std::vector<unsigned int> indecies,
                       VertexBufferLayout layout,
                       const std::string shader, const std::string texture)
        : m_Translation(glm::vec3(0, 0, 0)), m_VBuffer(vertices),
          m_Indices(indecies) { // do something about the translation
    //blending for transparency
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(m_VBuffer.data(), sizeof(Vertex) * 4);

    m_Layout = std::make_unique<VertexBufferLayout>(layout);
    m_Shader = std::make_unique<Shader>(shader);
    m_Shader->Bind();
    m_Texture = std::make_unique<Texture>(texture);

    m_VAO->AddBuffer(*m_VBO, *m_Layout);

    m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size());

}

Renderable::~Renderable() {
 //clear up things
}


void Renderable::OnUpdate(float dt) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
    auto m_View = glm::translate(glm::mat4(1.0f) ,glm::vec3(0,0,0));
    auto m_Projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    m_Texture->Bind();
    glm::mat4 mvp = model * m_View * m_Projection;
    m_Shader->Bind();
    m_Shader->SetUniform1f("u_dt",dt);
    m_Shader->SetUniform1i("u_Texture",0);
    m_Shader->SetUniformMat4f("u_MVP", mvp);
}

void Renderable::OnRender() {
    m_Shader->Bind();
    m_Texture->Bind();
    Renderer renderer;
    m_VAO->Bind();
    renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
}


void Renderable::OnImGuiRender() {
}

void Renderable::UpdateBuffer(std::vector<Vertex> nBuffer){
    m_VBuffer.swap(nBuffer);
    m_VBO->UpdateBuffer(m_VBuffer.data(), sizeof(Vertex) * m_VBuffer.size());
    m_VAO->AddBuffer(*m_VBO, *m_Layout);
}