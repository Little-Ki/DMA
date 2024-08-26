#include "dma_scatter.h"
#include "dma_device.h"
#include "log.hpp"

DMAScatter::DMAScatter(VMMDLL_SCATTER_HANDLE handle, DWORD pid) : m_handle(handle), m_pid(pid)
{
}

bool DMAScatter::avaliable()
{
    return m_handle && DMA::avaliable();
}

void DMAScatter::retrieve(void *buffer, void *target, size_t size)
{
    if (!avaliable())
    {
        Log::print("Scatter retrieve unavaliable!");
        return;
    }

    DWORD readed = 0;
    if (!VMMDLL_Scatter_Read(m_handle, reinterpret_cast<ULONG64>(target), size, static_cast<PBYTE>(buffer), &readed))
        Log::print("Scatter read for %p failed partly or full! Bytes written: %d/%d", target, readed, size);
}

void DMAScatter::close()
{
    if (!avaliable())
        return;

    VMMDLL_Scatter_CloseHandle(m_handle);

    m_handle = nullptr;
}

void DMAScatter::queueReadEx(uintptr_t address, void *buffer, size_t size)
{
    if (!avaliable())
    {
        return;
    }

    DWORD prepared = NULL;
    if (!VMMDLL_Scatter_PrepareEx(m_handle, address, size, static_cast<PBYTE>(buffer), &prepared))
    {
        Log::print("Failed to prepare scatter read at 0x%p", address);
    }
}

void DMAScatter::executeRead()
{
    if (!avaliable())
    {
        return;
    }

    if (!VMMDLL_Scatter_ExecuteRead(m_handle))
    {
        Log::print("Failed to execute scatter read\n");
    }

    if (!VMMDLL_Scatter_Clear(m_handle, m_pid, NULL))
    {
        Log::print("Failed to clear read scatter");
    }
}

void DMAScatter::queueWriteEx(uintptr_t address, void *buffer, size_t size)
{
    if (!avaliable())
    {
        return;
    }

    if (!VMMDLL_Scatter_PrepareWrite(m_handle, address, static_cast<PBYTE>(buffer), size))
    {
        Log::print("Failed to prepare scatter write at 0x%p", address);
    }
}

void DMAScatter::executeWrite()
{

    if (!avaliable())
    {
        return;
    }
    if (!VMMDLL_Scatter_Execute(m_handle))
    {
        Log::print("Failed to execute scatter write\n");
    }

    if (!VMMDLL_Scatter_Clear(m_handle, m_pid, NULL))
    {
        Log::print("Failed to clear write scatter\n");
    }
}

DMAScatter::~DMAScatter()
{
    close();
}
