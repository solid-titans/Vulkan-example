#include "VulkanRenderer.hpp"
#include <string.h>

VulkanRenderer::VulkanRenderer() {

}

int VulkanRenderer::init(GLFWwindow *newWindow) {
    window = newWindow;

    try {
        createInstance();
        getPhysicalDevice();
        createLogicalDevice();
    
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
    appInfo.apiVersion          = VK_API_VERSION_1_2;                      // Versao do Vulkan

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

void VulkanRenderer::getPhysicalDevice() {
    // Numerar quantas GPUs a maquina possui
    uint32_t deviceCounter = 0;

    vkEnumeratePhysicalDevices(instance, &deviceCounter, nullptr);

    // Se nao encontrar dispositivos que suportem vulkan
    if (deviceCounter == 0) {
        throw std::runtime_error("Não foram encontradas GPUs que suportem Vulkan!");

    }

    // Pegar a lista das GPUs
    std::vector<VkPhysicalDevice> deviceList(deviceCounter);
    vkEnumeratePhysicalDevices(instance, &deviceCounter, deviceList.data());

    for(const auto &device : deviceList) {
        if(checkDeviceSuitable(device)) {
            mainDevice.physicalDevice = device;
            break;

        }

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

bool VulkanRenderer::checkDeviceSuitable(VkPhysicalDevice device) {
    /*
    // Informacao do dispositivo
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    // Informacoes sobre o que a GPU pode fazer
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    */

    QueueFamilyIndices indices = getQueueFamilies(device);

    return indices.isValid();
}

QueueFamilyIndices VulkanRenderer::getQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    // Pegar todas as informacoes de uma GPU
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyList);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyList.data());

    // Verificar se o dispositivo suporta pelo menos um tipo de fila Familia
    int i = 0;
    for(const auto &queueFamily : queueFamilyList) {
        // Checar se a fila de familia possui pelo menos uma fila suportada
        // Filas podem ser de varios tipos definidas por uma bitfield. Precisa de um bitwise AND com VK_QUEUE_*_BIT para ver se há pelo menos um suportado
        if(queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;         // Se a fila de Familia for valida, então pegar o index

        }

        // Checar se uma fila de familia é válida, caso seja, pare de procurar
        if(indices.isValid()) {
            break;

        }

        i++;
    }

    return indices;
}

void VulkanRenderer::createLogicalDevice() {
    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

}