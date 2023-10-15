#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {
    TestTexture2D::TestTexture2D()
     :m_Count(10),
     m_View(glm::translate(glm::mat4(1.0f) ,glm::vec3(0,0,0))),
     m_Projection(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
{
        for(int i=0;i<m_Count;i++){
            int x = rand() % 960 ;
            int y = rand() % 540;
            m_Translations.emplace_back(x,y,0);
        }
        float positions[] = {
                -50.0f, 50.0f, 0.0f, 1.0f, //bottom right
                50.0f,  50.0f, 1.0f, 1.0f, //top right
                50.0f, -50.0f, 1.0f, 0.0f, //top left
                -50.0f, -50.0f, 0.0f, 0.0f //bottom left
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0};

        //blending for transparency
        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        m_VBO=std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2); //vertex location  0.5,-0.5...
        layout.Push(GL_FLOAT, 2); //texture coord 0.0f, 1.0f...

        m_VAO->AddBuffer(*m_VBO, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices,6);

        m_Shader = std::make_unique<Shader>("../res/shaders/shader.glsl");
        m_Shader->Bind();
        //before creating texture bind shader
        m_Texture = std::make_unique<Texture>("../res/textures/texture.png");
        //tell the shader to use texture ( 0 cuz slot 0 default change it if needed)
        m_Shader->SetUniform1i("u_Texture",0);
    }

    void TestTexture2D::OnUpdate(float dt) {
        m_Shader->SetUniform1f("u_dt",dt);
        int currElements = m_Translations.size();
        if(currElements>m_Count){
            while (currElements>m_Count) {
                m_Translations.pop_back();
                currElements--;
            }
        }else{
            for(int i=currElements;i<m_Count;i++){
                int x = rand() % 960 ;
                int y = rand() % 540;
                m_Translations.emplace_back(x,y,0);
            }
        }
    }

    void TestTexture2D::OnRender() {
        //clear screen
        GL_CALL(glClearColor(0.0f,0.0f,0.0f,0.0f));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        m_Texture->Bind();
        Renderer renderer;
        for(int i =0;i<m_Count;i++){
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translations[i]);
            glm::mat4 mvp = m_Projection * m_View * model;

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::OnImGuiRender() {

        ImGuiIO& io = ImGui::GetIO();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::SliderInt("count", &m_Count,0.,1000);

        for(int i=0;i<m_Count;i++){
            std::string label = "T: "+ std::to_string(i);;
            ImGui::SliderFloat3(label.c_str(), &m_Translations[i].x,0.0f,960.0f);
        }
    }
}