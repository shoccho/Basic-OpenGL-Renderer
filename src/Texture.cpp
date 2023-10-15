#include "Texture.h"

#include "Renderer.h"
#include "stb_image.h"

Texture::Texture(const std::string& path)
    : m_RendererId(0), m_Filepath(path),m_LocalBuffer(nullptr),
    m_Width(0),m_Height(0),m_BPP(0)
{
    GL_CALL(glGenTextures(1, &m_RendererId));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererId));

    //flips vertically cause opengl bottom 0,0 but image top right is 0,0
    stbi_set_flip_vertically_on_load(1);

    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    //wrapping texture
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

    GL_CALL(glBindTexture(GL_TEXTURE_2D,0));

    if (m_LocalBuffer){
        stbi_image_free(m_LocalBuffer);
    }
}

Texture::~Texture() {
    GL_CALL(glDeleteTextures(1, &m_RendererId));
}

void Texture::Unbind() const {

    GL_CALL(glBindTexture(GL_TEXTURE_2D,0));
}

void Texture::Bind(unsigned int slot) const {

    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

int Texture::getMWidth() const {
    return m_Width;
}

int Texture::getMHeight() const {
    return m_Height;
}

int Texture::getMBpp() const {
    return m_BPP;
}