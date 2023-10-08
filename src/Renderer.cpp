#include <iostream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

void GlClearError()
{
  while (glGetError())
    ;
}

bool GlLogCall(std::string function, std::string fileName, int line)
{
  while (GLenum error = glGetError())
  {
    std::cout << "[OPENGL Error:] ( " << error << " ) at \n"
              << "line: " << line << " of function: " << function << " in file: " << fileName << std::endl;
    return false;
  }
  return true;
}

void Renderer::Clear() const {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

