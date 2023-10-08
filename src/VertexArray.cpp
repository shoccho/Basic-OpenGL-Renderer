#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    GL_CALL(glGenVertexArrays(1, &m_RendererId));
}
VertexArray::~VertexArray()
{
    GL_CALL(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto &elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];

        GL_CALL(glEnableVertexAttribArray(i));
        GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void *)(uintptr_t)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GL_CALL(glBindVertexArray(m_RendererId));
}
void VertexArray::Unbind() const
{
    GL_CALL(glBindVertexArray(0));
}
