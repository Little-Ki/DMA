#pragma once

#include "dma.h"

#define DLL_EXPORT extern "C" __declspec(dllexport)

DLL_EXPORT uint32_t CreateDMA();

DLL_EXPORT bool InitializeDMA(uint32_t dma_id);

DLL_EXPORT void CloseDMA(uint32_t dma_id);

DLL_EXPORT bool OpenProcess(uint32_t dma_id, const wchar_t* wname);

DLL_EXPORT float ReadFloat(uint32_t dma_id, uintptr_t address);

DLL_EXPORT bool WriteFloat(uint32_t dma_id, uintptr_t address, float value);

DLL_EXPORT int ReadInt(uint32_t dma_id, uintptr_t address);

DLL_EXPORT bool WriteInt(uint32_t dma_id, uintptr_t address, int value);

