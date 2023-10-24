#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class QuadUtils {
public:
    static std::vector<unsigned int> GetQuadIndices() {
        return {
                0, 1, 2,
                2, 3, 0,
        };
    };

    static VertexBufferLayout GetQuadLayout() {
        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);  // Vertex location
        layout.Push(GL_FLOAT, 4);  // Color
        layout.Push(GL_FLOAT, 2);  // Texture coordinates
        layout.Push(GL_FLOAT, 1);  // Shader
        return layout;
    }

    static std::vector<Vertex> CreateQuadVertices(float x, float y, float size, float texId) {
        Vertex v0;
        v0.Position = glm::vec3(x, y, 0.0f);
        v0.Color = glm::vec4(0.1f, 0.2f, 0.6f, 1.0f);
        v0.TexCoords = glm::vec2(0.0f, 0.0f);
        v0.TexId = texId;

        Vertex v1;
        v1.Position = glm::vec3(x + size, y, 0.0f);
        v1.Color = glm::vec4(0.1f, 0.2f, 0.6f, 1.0f);
        v1.TexCoords = glm::vec2(1.0f, 0.0f);
        v1.TexId = texId;

        Vertex v2;
        v2.Position = glm::vec3(x + size, y + size, 0.0f);
        v2.Color = glm::vec4(0.1f, 0.2f, 0.6f, 1.0f);
        v2.TexCoords = glm::vec2(1.0f, 1.0f);
        v2.TexId = texId;

        Vertex v3;
        v3.Position = glm::vec3(x, y + size, 0.0f);
        v3.Color = glm::vec4(0.1f, 0.2f, 0.6f, 1.0f);
        v3.TexCoords = glm::vec2(0.0f, 1.0f);
        v3.TexId = texId;
        return {v0, v1, v2, v3};
    }
};
