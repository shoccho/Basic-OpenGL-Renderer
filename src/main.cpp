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
#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

void errorCallback(int code, const char* msg){
    std::cout<<"error "<<code<<" msg "<<msg<<std::endl;
}

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
    glfwSwapInterval(1);
    glfwSetErrorCallback(errorCallback);
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GL: " << glGetString(GL_VERSION) << std::endl;

    //tests
    test::Test* currentTest = nullptr;
    auto* menu = new test::TestMenu(currentTest);
    currentTest = menu;

    menu->AddTest<test::TestClearColor>("Clear Color");

    menu->AddTest<test::TestTexture2D>("Texture 2D");
    float dt=0;
    //scope for rendering
    {
        Renderer renderer;
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            //imgui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if(currentTest) {
                currentTest->OnUpdate(dt);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if(currentTest != menu && ImGui::Button("<-")){
                    delete currentTest;
                    currentTest = menu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }


            //end of redundant code
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
            dt+=0.05;

        }
        if(currentTest != menu){
            delete menu;
        }
        delete currentTest;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
