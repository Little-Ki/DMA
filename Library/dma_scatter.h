#pragma once
#include "vmmdll.h"

class DMA;

class DMAScatter
{
public:
    DMAScatter(DMA * dma);

    void create(VMMDLL_SCATTER_HANDLE handle, DWORD pid);

    bool avaliable();

    void retrieve(void* buffer, void* target, size_t size);

    void close();

    void queueReadEx(uintptr_t address, void* buffer, size_t size);

    void executeRead();

    void queueWriteEx(uintptr_t address, void* buffer, size_t size);

    void executeWrite();

    ~DMAScatter();

private:
    VMMDLL_SCATTER_HANDLE m_handle{ 0 };

    DWORD m_pid{ 0 };

    DMA* m_dma;
};