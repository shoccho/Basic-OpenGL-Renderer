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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // smooth interval?? vsync?
    glfwSwapInterval(1);

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
                100.0f, 200.0f, 0.0f, 1.0f, //bottom right
                200.0f,  200.0f, 1.0f, 1.0f, //top right
                200.0f, 100.0f, 1.0f, 0.0f, //top left
                100.0f, 100.0f, 0.0f, 0.0f //bottom left
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

        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f) ,glm::vec3(-100,0,0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200,200,0));
        glm::mat4 mvp =proj * view *  model ;
        Shader shader("../res/shaders/shader.glsl");
        Texture texture("../res/textures/texture.png");

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        texture.Unbind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            //have proper materials and remove this code from here
            shader.Bind();

            texture.Bind();
            //tell the shader to use texture ( 0 cuz slot 0 default change it if needed)

            shader.SetUniformMat4f("u_MVP", mvp);
            shader.SetUniform1i("u_Texture",0);
            shader.SetUniform1f("u_dt", dt);
            renderer.Draw(va,ib,shader);

            dt += 0.05;
            //end of redundant code

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        // glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}
