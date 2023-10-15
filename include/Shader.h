#pragma once

#include <string>
#include <unordered_map>

struct ShaderSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
private:
    unsigned int m_RendererId;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UniformLocations;

public:
    Shader(const std::string &filepath);
    ~Shader();

    void SetUniform1f(const std::string &name, float v0);
    void SetUniform1i(const std::string &name, int v0);

    void Bind() const;
    void Unbind() const;

private:
    int getUniformLocation(const std::string &name);
    unsigned int CreateShader(const std::string &vertexShader,
                              const std::string &fragmentShader);
    ShaderSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &text);
};
