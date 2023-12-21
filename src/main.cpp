#include "glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void static InitializeGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* CreateWindow()
{
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    return window;
}

int main()
{
    InitializeGlfw();
    GLFWwindow* window = CreateWindow();

    if(window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);

        processInput(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}