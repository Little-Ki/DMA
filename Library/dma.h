#pragma once
#include <Windows.h>
#include <string>

#include "vmmdll.h"

#include "dma_scatter.h"

class DMA
{
public:
    struct LibModules
    {
        HMODULE VMM{ nullptr };
        HMODULE FTD3XX{ nullptr };
        HMODULE LEECHCORE{ nullptr };
    };

    struct ProcessInfo
    {
        DWORD pid;
        uintptr_t moduleBase = 0;
        std::string name = "";
    };

public:
    DMA();

    bool initialize();

    const VMM_HANDLE handle();

    bool valid() const;

    bool openProcess(const std::wstring& wname);

    const DMAScatter& scatter();

    uintptr_t moduleBase(const std::wstring& wname);

    void close();

    template <typename T, typename Addr>
    T read(Addr address)
    {
        T buffer{};
        DWORD readed = 0;
        if (!valid() || !m_process.pid)
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
        if (!valid() || !m_process.pid)
        {
            return false;
        }

        return VMMDLL_MemWrite(
            m_handle, m_process.pid,
            reinterpret_cast<uintptr_t>(address),
            reinterpret_cast<PBYTE>(&value),
            sizeof(T));
    }


private:
    LibModules m_modules;

    VMM_HANDLE m_handle{ nullptr };

    ProcessInfo m_process;

    DMAScatter m_scatter;
    
};