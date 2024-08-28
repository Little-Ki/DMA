#pragma once

#include "Memory\Memory.h"

#define DLL_EXPORT extern "C" __declspec(dllexport)

DLL_EXPORT bool Initialize(const char* processName);

DLL_EXPORT bool InitKeyboard();

DLL_EXPORT bool IsKeyDown(uint32_t vk);

DLL_EXPORT uintptr_t GetModuleBase(const char* moduleName);

DLL_EXPORT DWORD GetProcessID();

DLL_EXPORT float ReadFloat(uintptr_t address);

DLL_EXPORT void WriteFloat(uintptr_t address, float value);

DLL_EXPORT int ReadInt(uintptr_t address);

DLL_EXPORT void WriteInt(uintptr_t address, int value);