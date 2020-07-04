#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

int main(void) {

    // Inicializar o glfw para criar uma janela
    glfwInit();

    // Criando Janela
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Vulkan API", nullptr, nullptr);

    // Loop para manter a janela aberta
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

    }

    // Desligando o programa
    glfwDestroyWindow(window); // Destruindo a janela
    return 0;
}