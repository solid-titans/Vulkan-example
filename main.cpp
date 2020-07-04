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

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    printf("Extension count: %i\n", extensionCount);

    glm::mat4 testMatrix(1.0f);
    glm::vec4 testVector(1.0f);

    auto testResult = testMatrix * testVector;

    // Loop para manter a janela aberta
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

    }

    // Desligando o programa
    glfwDestroyWindow(window); // Destruindo a janela
    glfwTerminate();           // Terminando a aplicacao
    return 0;
}