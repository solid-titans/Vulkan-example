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
    void cleanup();

    ~VulkanRenderer();


    private:
    GLFWwindow *window;

    // Componentes do Vulkan
    VkInstance instance;
    struct {
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
    } mainDevice;

    // Funcoes do Vulkan
    // - Criar funcoes
    void createInstance();

    // - Funcoes GET
    void getPhysicalDevice();

    // - Funcoes de suporte
    bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
};

#endif