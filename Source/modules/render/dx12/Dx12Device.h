#pragma once

#ifndef INCLUDED_T_DEVICE_H
#include <TDevice.h>
#endif

#include <coalpy.render/Resources.h>
#include <coalpy.render/ShaderDefs.h>
#include <unordered_map>
#include <d3d12.h>
#include <string>

struct IDXGIFactory2;
struct ID3D12Device2;
struct ID3D12Debug;
struct ID3D12RootSignature; 
struct ID3D12CommandSignature;
struct ID3D12Pageable;

namespace coalpy
{

class Dx12ShaderDb;

namespace render
{

class Dx12Queues;
class Dx12DescriptorPool;
class Dx12ResourceCollection;
class Dx12BufferPool;
class Dx12CounterPool;
class Dx12MarkerCollector;
class Dx12Gc;
class Dx12PixApi;
struct Dx12WorkInformationMap;

class Dx12Device : public TDevice<Dx12Device>
{
public:
    enum class TableTypes : int
    {
        Srv, Uav, Cbv, Sampler, Count
    };

    static IDXGIFactory2* dxgiFactory();

    Dx12Device(const DeviceConfig& config);
    virtual ~Dx12Device();

    static void enumerate(std::vector<DeviceInfo>& outputList);

    virtual TextureResult createTexture(const TextureDesc& desc) override;
    virtual TextureResult recreateTexture(Texture texture, const TextureDesc& desc) override;
    virtual BufferResult  createBuffer (const BufferDesc& config) override;
    virtual SamplerResult createSampler (const SamplerDesc& config) override;
    virtual InResourceTableResult createInResourceTable  (const ResourceTableDesc& config) override;
    virtual OutResourceTableResult createOutResourceTable (const ResourceTableDesc& config) override;
    virtual SamplerTableResult  createSamplerTable (const ResourceTableDesc& config) override;
    virtual void getResourceMemoryInfo(ResourceHandle handle, ResourceMemoryInfo& memInfo) override;
    virtual WaitStatus waitOnCpu(WorkHandle handle, int milliseconds = 0) override;
    virtual DownloadStatus getDownloadStatus(WorkHandle bundle, ResourceHandle handle, int mipLevel, int arraySlice) override;
    virtual void release(ResourceHandle resource) override;
    virtual void release(ResourceTable table) override;
    virtual const DeviceInfo& info() const override { return m_info; }
    virtual const DeviceRuntimeInfo& runtimeInfo() const { return m_runtimeInfo; }
    virtual SmartPtr<IDisplay> createDisplay(const DisplayConfig& config) override;
    virtual void* mappedMemory (Buffer buffer) override;

    virtual void removeShaderDb() { m_shaderDb = nullptr; }
    virtual IShaderDb* db() override { return (IShaderDb*)m_shaderDb; }

    void internalReleaseWorkHandle(WorkHandle handle);

    virtual void beginCollectMarkers(int maxQueryBytes) override;
    virtual MarkerResults endCollectMarkers() override;

    //utility for internal transitioning.
    void transitionResourceState(ResourceHandle resource, D3D12_RESOURCE_STATES newState, std::vector<D3D12_RESOURCE_BARRIER>& outBarriers);

    ID3D12Device2& device() { return *m_device; }
    Dx12Queues& queues() { return *m_queues; }
    Dx12ResourceCollection& resources() { return *m_resources; }
    Dx12CounterPool& counterPool() { return *m_counterPool; }
    Dx12DescriptorPool& descriptors() { return *m_descriptors; }
    Dx12ShaderDb& shaderDb() { return *m_shaderDb; }
    Dx12BufferPool& readbackPool() { return *m_readbackPool; }
    Dx12MarkerCollector& markerCollector() { return *m_markerCollector; }
    Dx12Gc& gc() { return *m_gc; }
    WorkBundleDb& workDb() { return m_workDb; } 


    ID3D12RootSignature& defaultComputeRootSignature() const { return *m_computeRootSignature; }
    ID3D12CommandSignature& indirectDispatchSignature() const { return *m_indirectDispatchCommandSignature; }

    int tableIndex(TableTypes type, int registerSpace) const
    {
        CPY_ASSERT(registerSpace < (int)m_maxResourceTables);
        return (int)type * (int)m_maxResourceTables + (registerSpace & 0x7);
    }

    ScheduleStatus internalSchedule(CommandList** commandLists, int listCounts, WorkHandle workHandle); 

    void deferRelease(ID3D12Pageable& object);

    Buffer countersBuffer() { return m_countersBuffer; }

    Dx12PixApi* getPixApi() const;

private:
    ID3D12Debug* m_debugLayer;
    ID3D12Device2* m_device;
    ID3D12RootSignature* m_computeRootSignature;
    ID3D12CommandSignature* m_indirectDispatchCommandSignature;

    Dx12CounterPool* m_counterPool;
    Dx12ResourceCollection* m_resources;
    Dx12DescriptorPool* m_descriptors;
    Dx12Queues* m_queues;
    Dx12BufferPool* m_readbackPool;
    Dx12ShaderDb* m_shaderDb;
    Dx12MarkerCollector* m_markerCollector;
    Dx12Gc* m_gc;
    DeviceInfo m_info;
    DeviceRuntimeInfo m_runtimeInfo;

    Dx12WorkInformationMap* m_dx12WorkInfos;

    Buffer m_countersBuffer;

    ShaderModel m_supportedSM;
    unsigned m_maxResourceTables;
};

}
}

