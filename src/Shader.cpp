#include "Shader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "Renderer.h"

Shader::Shader(const std::string &filepath)
    : m_RendererId(0), m_Filepath(filepath)
{
    ShaderSource source = ParseShader(filepath);
    m_RendererId = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
    GL_CALL(glDeleteProgram(m_RendererId));
}

ShaderSource Shader::ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

void Shader::Bind() const
{
    GL_CALL(glUseProgram(m_RendererId));
}

void Shader::Unbind() const
{
    GL_CALL(glUseProgram(0))
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &text)
{
    uint id = glCreateShader(type);
    const char *src = text.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Shader Error: " << message << "\n";
        glDeleteShader(id);
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader,
                                  const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::SetUniform1f(const std::string &name, float v0)
{
    GL_CALL(glUniform1f(getUniformLocation(name), v0));
}
int Shader::getUniformLocation(const std::string &name)
{
    if( m_UniformLocations.find(name) != m_UniformLocations.end()){
        return m_UniformLocations[name];
    }

    int location = glGetUniformLocation(m_RendererId, name.c_str());
    m_UniformLocations[name] = location;
    return location;
}
