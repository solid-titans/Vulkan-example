#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include "VulkanRenderer.hpp"

GLFWwindow *window;
VulkanRenderer vulkanRenderer;

// Inicializando a janela
void initWindow(std::string wName = "Example", const int width = 800, const int heigth = 600) {
    // Inicializar GLFW
    glfwInit();

    // Nao usar OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, heigth, wName.c_str(), nullptr, nullptr);
}

int main(void) {
    // Criar a janela
    initWindow("Vulkan test", 800, 600);

    // Criar uma instancia do Vulkan 
    if(vulkanRenderer.init(window) == EXIT_FAILURE) {
        return EXIT_FAILURE;

    }

    // Loop da janela
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

    }

    vulkanRenderer.cleanup();   // Limpar as instancias do vulkan

    // Desligando a janela
    glfwDestroyWindow(window);  // Desligando a janela do app
    glfwTerminate();            // Desligando o glfw
    return 0;
}