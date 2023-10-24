#pragma once

#include "Renderable.h"
#include "glm/glm.hpp"

class Quad : public Renderable {
public:
    Quad(const glm::vec2 position,
         const float size,
         const std::string shader, const std::string texture);

    void OnUpdate(float dt) override;

    void OnImGuiRender() override;

private:
    glm::vec2 m_Position;
    glm::vec2 m_Direction;
};