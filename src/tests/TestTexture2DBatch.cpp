#include "TestTexture2DBatch.h"

#include "Renderer.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"

namespace test {

    static std::array<Vertex ,4> CreateQuad(float x, float y, float texId){
        float size = 50.0f;
        Vertex v0;
        v0.Position = glm::vec3(x,y,0.0f);
        v0.Color = glm::vec4(0.1f,0.2f,0.6f,1.0f);
        v0.TexCoords = glm::vec2(0.0f, 0.0f);
        v0.TexId = texId;

        Vertex v1;
        v1.Position = glm::vec3(x+size,y,0.0f);
        v1.Color = glm::vec4(0.1f,0.2f,0.6f,1.0f);
        v1.TexCoords = glm::vec2(1.0f, 0.0f);
        v1.TexId = texId;

        Vertex v2;
        v2.Position = glm::vec3(x+size,y+size,0.0f);
        v2.Color = glm::vec4(0.1f,0.2f,0.6f,1.0f);
        v2.TexCoords = glm::vec2(1.0f, 1.0f);
        v2.TexId = texId;

        Vertex v3;
        v3.Position = glm::vec3(x,y+size,0.0f);
        v3.Color = glm::vec4(0.1f,0.2f,0.6f,1.0f);
        v3.TexCoords = glm::vec2(0.0f, 1.0f);
        v3.TexId = texId;
        return {v0, v1, v2, v3};
    }

    TestTexture2DBatch::TestTexture2DBatch()
     :m_Count(2),
      m_View(glm::translate(glm::mat4(1.0f) ,glm::vec3(0,0,0))),
      m_Projection(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
    {
        m_Translation = glm::vec3(0,0,0);
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0,
        };
        for(int i =0; i< m_Count;i++){
            for(auto j: indices) {
                m_Indices.push_back(j+(i*4));
            }
        }


        //blending for transparency
        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        for( int i =0;i < m_Count;i++) {
            float a = rand() % 960;
            float b = rand() % 540;
            auto q0 = CreateQuad(a, b, rand()%2);
            m_VBuffer.push_back(q0[0]);
            m_VBuffer.push_back(q0[1]);
            m_VBuffer.push_back(q0[2]);
            m_VBuffer.push_back(q0[3]);
        }
        m_VBO=std::make_unique<VertexBuffer>(m_VBuffer.data(), sizeof(Vertex)*8);

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3); //vertex location  0.5,-0.5...
        layout.Push(GL_FLOAT, 4); //color  0.5,-0.5...
        layout.Push(GL_FLOAT, 2); //texture coord 0.0f, 1.0f...
        layout.Push(GL_FLOAT, 1); // which shader

        m_VAO->AddBuffer(*m_VBO, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(),m_Indices.size());

        m_Shader = std::make_unique<Shader>("../res/shaders/shaderBatch.glsl");
        m_Shader->Bind();
        //before creating texture bind shader
        m_Texture1= std::make_unique<Texture>("../res/textures/texture.png");
        m_Texture2 = std::make_unique<Texture>("../res/textures/texture2.png");

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
    }

    void TestTexture2DBatch::OnUpdate(float dt) {
        m_VBO->Bind();

        int currentItems = m_VBuffer.size()/4;
        if (currentItems!=m_Count) {
            if (currentItems > m_Count) {
                m_VBuffer.resize(m_Count*4);
                m_Indices.resize(m_Count*6);
            }
            if (currentItems < m_Count) {
                for (int i = 0; i < (m_Count - currentItems); i++) {
                    float a = rand() % 960;
                    float b = rand() % 540;
                    auto q0 = CreateQuad(a, b, rand() % 2);
                    m_VBuffer.push_back(q0[0]);
                    m_VBuffer.push_back(q0[1]);
                    m_VBuffer.push_back(q0[2]);
                    m_VBuffer.push_back(q0[3]);

                    unsigned int indices[] = {
                            0, 1, 2,
                            2, 3, 0,
                    };
                    for(auto j: indices) {
                        m_Indices.push_back(j+((currentItems+i)*4));
                    }
                }
            }
            m_VBO->UpdateBuffer(m_VBuffer.data(), sizeof(Vertex) * m_VBuffer.size());
            VertexBufferLayout layout;
            layout.Push(GL_FLOAT, 3);//vertex location  0.5,-0.5...
            layout.Push(GL_FLOAT, 4);//color  0.5,-0.5...
            layout.Push(GL_FLOAT, 2); //texture coord 0.0f, 1.0f...
            layout.Push(GL_FLOAT, 1); // which shader
            m_VAO->AddBuffer(*m_VBO,layout);
            auto t = std::make_unique<IndexBuffer>(m_Indices.data(),m_Indices.size());
            m_IndexBuffer.swap(t);
        }

        //clear screen
        GL_CALL(glClearColor(0.0f,0.0f,0.0f,0.0f));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        int idx[2] = {0,1};

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
        glm::mat4 mvp = m_Projection * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniform1f("u_dt",dt);

        m_Shader->SetUniform1iv("u_Textures",2, idx);
        m_Shader->SetUniformMat4f("u_MVP", mvp);
    }

    void TestTexture2DBatch::OnRender() {
        Renderer renderer;
        m_VAO->Bind();
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestTexture2DBatch::OnImGuiRender() {

        ImGuiIO& io = ImGui::GetIO();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::SliderInt("count", &m_Count,0.,100000);
    }
}