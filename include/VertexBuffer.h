#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoords;
    float TexId;
};

class VertexBuffer
{
private:
    unsigned int m_RendererId;

public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void UpdateBuffer(const void *data, unsigned  int size);

    void Bind() const;
    void Unbind() const;
    
};
