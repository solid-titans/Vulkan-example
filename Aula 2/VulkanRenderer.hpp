#ifndef VulkanRenderer_h
#define VulkanRenderer_h

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

class VulkanRenderer {
    public:
    VulkanRenderer();

    int init(GLFWwindow *newWindow);   // Iniciar uma nova janela


    ~VulkanRenderer();


    private:
    GLFWwindow *window;

    // Componentes do Vulkan
    VkInstance instance;

    // Funcoes do Vulkan
    void createInstance();
};

#endif