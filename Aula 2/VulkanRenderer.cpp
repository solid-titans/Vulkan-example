#include "VulkanRenderer.hpp"
#include <string.h>

VulkanRenderer::VulkanRenderer() {

}

int VulkanRenderer::init(GLFWwindow *newWindow) {
    window = newWindow;

    try {
        createInstance();
        getPhysicalDevice();
    
    } catch(const std::runtime_error &e) {
        printf("ERROR: %s\n", e.what());
        return EXIT_FAILURE;
    }

    return 0;
}

VulkanRenderer::~VulkanRenderer() {

}

void VulkanRenderer::createInstance() {
    // Informacao sobre o app completo (nao so do vulkan)
    // Os codigos daqui nao alteram o codigo final eh apenas para debug
    VkApplicationInfo appInfo = {};
    appInfo.sType               = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    appInfo.pApplicationName    = "Vulkan app";                            // Nome customizado da aplicacao
    appInfo.applicationVersion  = VK_MAKE_VERSION(1, 0, 0);                // Versao customizada da aplicacao
    appInfo.pEngineName         = "lusantisuper Engine";                   // Nome da Engine da minha aplicacao
    appInfo.engineVersion       = VK_MAKE_VERSION(1, 0, 0);                // Versao da minha engine
    appInfo.apiVersion          = VK_API_VERSION_1_0;                      // Versao do Vulkan

    // Criando a informacao de uma instancia de Vulkan
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Criando uma lista para ter as extencoes da instancia
    std::vector<const char*> instanceExtensions = std::vector<const char*>();

    uint32_t glfwExtensionCount = 0;           // GLFW requere varias extencoes
    const char** glfwExtensions;               // Array de strings passadas como array de cstring (que sao ponteiros)

    // Pegando as extencoes da GLFW 
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Adicinando as exntensoes do GLFW na lista
    for(size_t i = 0; i < glfwExtensionCount; i++) {
        instanceExtensions.push_back(glfwExtensions[i]);

    }

    // Checando se as extensoes sao suportadas
    if(!checkInstanceExtensionSupport(&instanceExtensions)) {
        throw std::runtime_error("Extensoes do VK necessarias nao sao suportadas");

    }

    createInfo.enabledExtensionCount     = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames   = instanceExtensions.data();

    // TODO: Adicionar os layers de validacao da instancia que irei usar
    createInfo.enabledLayerCount         = 0;
    createInfo.ppEnabledLayerNames       = nullptr;

    // Criando a instancia
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if(result != VK_SUCCESS) {
        throw std::runtime_error("Falha ao criar uma instancia de Vulkan!");

    }
}

bool VulkanRenderer::checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions) {
    // Preciso do tamanho da lista antes de cria-la para criar um vector que possa suporta-la
    uint32_t extensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

    // Criar uma lista de vkExtensionProperties usando o count 
    std::vector<VkExtensionProperties> extensions(extensionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

    // Checando se as extensoes recebidas estao disponiveis
    for(const auto &checkExtension : *checkExtensions) {
        bool hasExtension = false;
        for(const auto &extension : extensions) {
            if(strcmp(checkExtension, extension.extensionName)) {
                hasExtension = true;
                break;

            }    
        }

        if(!hasExtension) {
            return false;

        }
    }

    return true;
}

void VulkanRenderer::cleanup() {
    vkDestroyInstance(instance, nullptr);

}