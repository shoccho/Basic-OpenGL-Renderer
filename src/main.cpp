#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // smooth interval?? vsync?
//    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GL: " << glGetString(GL_VERSION) << std::endl;

    //blending for transparency
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    float dt = 0;
    // Set the mouse callback function
    //  glfwSetCursorPosCallback(window, mouse_callback);
    {
        float positions[] = {
                -50.0f, 50.0f, 0.0f, 1.0f, //bottom right
                50.0f,  50.0f, 1.0f, 1.0f, //top right
                50.0f, -50.0f, 1.0f, 0.0f, //top left
                -50.0f, -50.0f, 0.0f, 0.0f //bottom left
        };

        uint indices[] = {
                0, 1, 2,
                2, 3, 0};

        VertexArray va;

        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2); //vertex location  0.5,-0.5...
        layout.Push(GL_FLOAT, 2); //texture coord 0.0f, 1.0f...

        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f) ,glm::vec3(0,0,0));
        glm::vec3 translation1 = glm::vec3(200,200,0);
        glm::vec3 translation2 = glm::vec3(400,400,0);

        Shader shader("../res/shaders/shader.glsl");
        Texture texture("../res/textures/texture.png");
        shader.Bind();

        //tell the shader to use texture ( 0 cuz slot 0 default change it if needed)
        shader.SetUniform1i("u_Texture",0);


        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        texture.Unbind();
        shader.Unbind();

        Renderer renderer;

        //imgui codes------------------
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            //imgui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("Hello, world!");
                ImGui::SliderFloat3("Translation 1", &translation1.x,0.0f,960.0f);

                ImGui::SliderFloat3("Translation 2", &translation2.x,0.0f,960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }
            texture.Bind();
            //have proper materials and remove this code from here
            shader.Bind();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation1);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va,ib,shader);
            }

//            shader.SetUniform1f("u_dt", dt);
            //second
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation2);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va,ib,shader);

            }
            dt += 0.05;
            //end of redundant code
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        // glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}
