
#include <sstream>
#include <filesystem>
#include "dma.h"
#include "log.hpp"

DMA::DMA(bool mmap)
{
    initialize(mmap);
}

bool DMA::initialize(bool mmap)
{
    if (m_handle)
        return true;

    m_modules.VMM = LoadLibraryA("vmm.dll");
    m_modules.FTD3XX = LoadLibraryA("FTD3XX.dll");
    m_modules.LEECHCORE = LoadLibraryA("leechcore.dll");

    if (!m_modules.VMM || !m_modules.FTD3XX || !m_modules.LEECHCORE)
    {
        Log::print("ERROR: could not load a library:");
        Log::print("vmm: %s", m_modules.VMM);
        Log::print("ftd: %s", m_modules.FTD3XX);
        Log::print("leech: %s", m_modules.LEECHCORE);
        return false;
    }

    LPSTR args[] = {"", "-device", "fpga", "-v", "", ""};
    DWORD argc = 4;
    

    if (mmap)
    {
        auto path = std::filesystem::temp_directory_path();
        path += (temp_path.string() + "\\mmap.txt");
    }

    m_handle = VMMDLL_Initialize(argc, args);

    if (!m_handle)
    {
        Log::print("Initialization failed! Is the DMA in use or disconnected?");
        return false;
    }

    Log::print("DMA initialize successfully!");

    return true;
}

const VMM_HANDLE DMA::handle()
{
    return m_handle;
}

bool DMA::avaliable()
{
    return m_modules.VMM && m_modules.FTD3XX && m_modules.LEECHCORE && m_handle;
}

DMAScatter DMA::createScatter(DWORD pid)
{
    if (!avaliable())
        return DMAScatter();

    auto handle = VMMDLL_Scatter_Initialize(m_handle, pid, VMMDLL_FLAG_NOCACHE);

    return DMAScatter(handle, pid);
}

bool DMA::openProcess(const std::wstring &wname)
{
    if (!avaliable())
        return false;

    const std::string name(wname.begin(), wname.end());

    DWORD pid = 0;

    if (!VMMDLL_PidGetFromName(m_handle, const_cast<char *>(name.c_str()), &pid))
    {
        Log::print("Process with name %s not found!", name.c_str());
        return 0;
    }

    m_process.moduleBase = VMMDLL_ProcessGetModuleBaseW(m_handle, m_process.pid, const_cast<LPWSTR>(wname.c_str()));

    return true;
}

uintptr_t DMA::moduleBase(const std::wstring &wname)
{
    if (!avaliable() || !m_process.pid)
        return 0;

    auto base = VMMDLL_ProcessGetModuleBaseW(m_handle, m_process.pid, const_cast<LPWSTR>(wname.c_str()));
    return base;
}

void DMA::close()
{
    if (!m_handle)
        return;

    VMMDLL_Close(m_handle);
    m_handle = nullptr;
}

bool DMA::dumpMemoryMap()
{
	LPSTR args[] = { (LPSTR)"", (LPSTR)"-device", (LPSTR)"fpga", (LPSTR)"-v" };
	int argc = 3;
    return false;
}
