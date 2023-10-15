#pragma once

#include <GL/glew.h>
#include <string>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"


// dbg macro assert to insert breakpoint
#define ASSERT(x) \
  if (!(x))       \
    __builtin_trap();

#define GL_CALL(x) \
  GlClearError();  \
  x;               \
  ASSERT(GlLogCall(#x, __FILE__, __LINE__));

void GlClearError();

bool GlLogCall(const std::string& function, const std::string& fileName, int line);

class Renderer{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};
