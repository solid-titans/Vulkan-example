#ifndef VulkanRenderer_h
#define VulkanRenderer_h

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "utilities.hpp"

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
    void createLogicalDevice();

    // - Funcoes GET
    void getPhysicalDevice();

    // - Funcoes de suporte
    // -- Funcoes de suporte
    bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
    bool checkDeviceSuitable(VkPhysicalDevice device);                               // Checar se o dispositivo suporta Vulkan

    // -- Funcoes de get
    QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
};

#endif