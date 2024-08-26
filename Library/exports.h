#pragma once

#include "dma.h"

#define DLL_EXPORT extern "C" __declspec(dllexport)

DLL_EXPORT uint32_t createDMA();

DLL_EXPORT bool initializeDMA(uint32_t id);