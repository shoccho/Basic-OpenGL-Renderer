#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>

//#define TESTS // <- uncomment to run tests instead of example quad

#include "Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#ifdef TESTS
#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestTexture2DBatch.h"
#else

#include "Scene.h"
#include "examples/Quad/Quad.h"

#endif

void errorCallback(int code, const char *msg) {
    std::cout << "error " << code << " msg " << msg << std::endl;
}

#ifndef TESTS
Scene scene;

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        auto quad = std::make_shared<Quad>(
               glm::vec2(xpos, 540 - ypos),
               100,
               "../res/shaders/quad.glsl",
               "../res/textures/texture.png");
        scene.AddNode("some", quad);
    }
}

#endif

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Basic renderer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // smooth interval?? vsync?
    glfwSwapInterval(1);
    glfwSetErrorCallback(errorCallback);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GL: " << glGetString(GL_VERSION) << std::endl;

#ifdef TESTS

    test::Test *currentTest = nullptr;
    auto *menu = new test::TestMenu(currentTest);
    currentTest = menu;

    menu->AddTest<test::TestClearColor>("Clear Color");
    menu->AddTest<test::TestTexture2D>("Texture 2D");
    menu->AddTest<test::TestTexture2DBatch>("Texture 2D Batch");
#else
    glfwSetMouseButtonCallback(window, mouse_button_callback);
#endif
    float dt = 0;
    //scope for rendering
    {
        Renderer renderer;
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        auto currentFrame = glfwGetTime();
        auto lastFrame = glfwGetTime();
        auto deltaTime = currentFrame - lastFrame;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();

            //imgui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
#ifdef TESTS
            if (currentTest) {
                currentTest->OnUpdate(dt);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != menu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = menu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }
#else
            ImGui::Begin("Menu");
            scene.OnUpdate(dt);
            scene.OnRender();
            scene.OnImGuiRender();
            ImGui::End();
#endif
            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            dt += deltaTime;
            lastFrame = currentFrame;
        }
#ifdef TESTS
        if(currentTest != menu){
            delete menu;
        }
        delete currentTest;
#endif
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
