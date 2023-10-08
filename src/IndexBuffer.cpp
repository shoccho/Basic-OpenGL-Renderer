#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
    : m_Count(count)
{
  GL_CALL(glGenBuffers(1, &m_RendererId));
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
  GL_CALL(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const
{
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::Unbind() const
{
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
