#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

float blueValue = 0.0f;
float redValue = 0.0f;
float dt = 0;

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

  // Set the mouse callback function
    //  glfwSetCursorPosCallback(window, mouse_callback);
  {
    float positions[8] = {
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
    };

    uint indices[] = {
        0, 1, 2,
        2, 3, 0};

    VertexArray va;

    VertexBuffer vb(positions, 8 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);

    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/shader.glsl");

    va.Unbind();
    vb.Unbind();
    ib.Unbind();

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      renderer.Clear();
      //have proper materials and remove this code from here
      shader.Bind();
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
