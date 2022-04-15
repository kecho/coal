#include <Config.h>
#if ENABLE_VULKAN

#include "VkDevice.h"
#include "VkShaderDb.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <set>
#include <vector>

const std::set<std::string>& getRequestedLayerNames()
{
    static std::set<std::string> layers;
    if (layers.empty())
    {
        layers.emplace("VK_LAYER_NV_optimus");
        layers.emplace("VK_LAYER_KHRONOS_validation");
    }
    return layers;
}

bool getAvailableVulkanLayers(std::vector<std::string>& outLayers)
{
    // Figure out the amount of available layers
    // Layers are used for debugging / validation etc / profiling..
    unsigned int instance_layer_count = 0;
    VkResult res = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
    if (res != VK_SUCCESS)
    {
        std::cout << "unable to query vulkan instance layer property count\n";
        return false;
    }

    std::vector<VkLayerProperties> instance_layer_names(instance_layer_count);
    res = vkEnumerateInstanceLayerProperties(&instance_layer_count, instance_layer_names.data());
    if (res != VK_SUCCESS)
    {
        std::cout << "unable to retrieve vulkan instance layer names\n";
        return false;
    }

    // Display layer names and find the ones we specified above
    std::cout << "found " << instance_layer_count << " instance layers:\n";
    std::vector<const char*> valid_instance_layer_names;
    const std::set<std::string>& lookup_layers = getRequestedLayerNames();
    int count(0);
    outLayers.clear();
    for (const auto& name : instance_layer_names)
    {
        std::cout << count << ": " << name.layerName << ": " << name.description << "\n";
        auto it = lookup_layers.find(std::string(name.layerName));
        if (it != lookup_layers.end())
            outLayers.emplace_back(name.layerName);
        count++;
    }

    // Print the ones we're enabling
    std::cout << "\n";
    for (const auto& layer : outLayers)
        std::cout << "applying layer: " << layer.c_str() << "\n";
    return true;
}

namespace coalpy
{
namespace render
{

VkDevice::VkDevice(const DeviceConfig& config)
: TDevice<VkDevice>(config),
  m_shaderDb(nullptr)
{
    if (config.shaderDb)
    {
        m_shaderDb = static_cast<VkShaderDb*>(config.shaderDb);
        CPY_ASSERT_MSG(m_shaderDb->parentDevice() == nullptr, "shader database can only belong to 1 and only 1 device");
        m_shaderDb->setParentDevice(this);
    }

    m_info = {};
    m_info.valid = true;
}

VkDevice::~VkDevice()
{
    if (m_shaderDb && m_shaderDb->parentDevice() == this)
        m_shaderDb->setParentDevice(nullptr);
}

void VkDevice::enumerate(std::vector<DeviceInfo>& outputList)
{
    std::vector<std::string> dummy;
    getAvailableVulkanLayers(dummy);
}

TextureResult VkDevice::createTexture(const TextureDesc& desc)
{
    return TextureResult();
}

TextureResult VkDevice::recreateTexture(Texture texture, const TextureDesc& desc)
{
    return TextureResult();
}

BufferResult  VkDevice::createBuffer (const BufferDesc& config)
{
    return BufferResult();
}

SamplerResult VkDevice::createSampler (const SamplerDesc& config)
{
    return SamplerResult();
}

InResourceTableResult VkDevice::createInResourceTable  (const ResourceTableDesc& config)
{
    return InResourceTableResult();
}

OutResourceTableResult VkDevice::createOutResourceTable (const ResourceTableDesc& config)
{
    return OutResourceTableResult();
}

SamplerTableResult  VkDevice::createSamplerTable (const ResourceTableDesc& config)
{
    return SamplerTableResult();
}

void VkDevice::getResourceMemoryInfo(ResourceHandle handle, ResourceMemoryInfo& memInfo)
{
    memInfo = ResourceMemoryInfo();
}

WaitStatus VkDevice::waitOnCpu(WorkHandle handle, int milliseconds)
{
    return WaitStatus();
}

DownloadStatus VkDevice::getDownloadStatus(WorkHandle bundle, ResourceHandle handle, int mipLevel, int arraySlice)
{
    return DownloadStatus();
}

void VkDevice::release(ResourceHandle resource)
{
}

void VkDevice::release(ResourceTable table)
{
}

SmartPtr<IDisplay> VkDevice::createDisplay(const DisplayConfig& config)
{
    return nullptr;
}

void VkDevice::internalReleaseWorkHandle(WorkHandle handle)
{
}

ScheduleStatus VkDevice::internalSchedule(CommandList** commandLists, int listCounts, WorkHandle workHandle)
{
    return ScheduleStatus();
}

}
}

#endif