#pragma once
#include <Windows.h>
#include <string>

#include "vmmdll.h"
#include "dma_scatter.h"
#include "dma_process.h"

class DMA
{
public:
    struct LibModules
    {
        HMODULE VMM{nullptr};
        HMODULE FTD3XX{nullptr};
        HMODULE LEECHCORE{nullptr};
    };

    struct ProcessInfo
    {
        DWORD pid;
        uintptr_t moduleBase = 0;
        std::string name = "";
    };

public:
    DMA() = default;

    DMA(bool mmap = true);

    bool initialize(bool mmap = true);

    const VMM_HANDLE handle();

    bool avaliable();

    template <typename T, typename Addr>
    T read(Addr address)
    {
        T buffer{};
        DWORD readed = 0;
        if (!avaliable() || !m_process.pid)
        {
            return buffer;
        }

        VMMDLL_MemReadEx(
            m_handle, m_process.pid,
            reinterpret_cast<uintptr_t>(address),
            reinterpret_cast<PBYTE>(&buffer),
            sizeof(T), &readed,
            VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING | VMMDLL_FLAG_ZEROPAD_ON_FAIL | VMMDLL_FLAG_NOPAGING_IO);

        return buffer;
    }

    template <typename T, typename Addr>
    bool write(Addr address, T value)
    {
        if (!avaliable() || !m_process.pid)
        {
            return false;
        }

        return VMMDLL_MemWrite(
            m_handle, m_process.pid,
            reinterpret_cast<uintptr_t>(address),
            reinterpret_cast<PBYTE>(&value),
            sizeof(T));
    }

    DMAScatter createScatter(DWORD pid);

    bool openProcess(const std::wstring &wname);

    uintptr_t moduleBase(const std::wstring &wname);

    void close();

private:
    LibModules m_modules;

    VMM_HANDLE m_handle{nullptr};

    ProcessInfo m_process;
};