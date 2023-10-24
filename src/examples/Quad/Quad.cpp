#include "Quad.h"
#include "QuadUtils.h"
#include "imgui.h"
#include "Renderable.h"

Quad::Quad(const glm::vec2 position,
           const float size,
           const std::string shader, const std::string texture) :
        m_Position(position),
        m_Direction(glm::vec2(std::rand() % 2 * 2 - 1, std::rand() % 2 * 2 - 1)),
        Renderable(QuadUtils::CreateQuadVertices(position.x, position.y, size, 0),
                   QuadUtils::GetQuadIndices(),
                   QuadUtils::GetQuadLayout(), shader, texture) {
}

void Quad::OnUpdate(float dt) {
    if (m_Position.x > 860)m_Direction.x = -1;
    else if (m_Position.x < 0) m_Direction.x = 1;
    if (m_Position.y > 440) m_Direction.y = -1;
    else if (m_Position.y < 0) m_Direction.y = 1;

    m_Position.x += (m_Direction.x * (10.0));
    m_Position.y += (m_Direction.y * (10.0));

    Renderable::UpdateBuffer(QuadUtils::CreateQuadVertices(m_Position.x, m_Position.y, 100.0f, 0));
    Renderable::OnUpdate(dt);
}

void Quad::OnImGuiRender() {
    ImGui::Text("Quad position %0.2f %0.2f", m_Position.x, m_Position.y);
}