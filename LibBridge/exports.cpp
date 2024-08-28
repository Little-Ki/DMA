#include "exports.h"

bool Initialize(const char* processName)
{
	return mem.Init(processName);
}

bool InitKeyboard() {
	return mem.GetKeyboard()->InitKeyboard();
}

bool IsKeyDown(uint32_t vk) {
	return mem.GetKeyboard()->IsKeyDown(vk);
}

uintptr_t GetModuleBase(const char* moduleName)
{
	return mem.GetBaseDaddy(moduleName);
}

DWORD GetProcessID() {
	return mem.GetProcessInformation().dwPID;
}


float ReadFloat(uintptr_t address) {
	return mem.Read<float>(address);
}

void WriteFloat(uintptr_t address, float value) {
	mem.Write<float>(address, value);
}

int ReadInt(uintptr_t address) {
	return mem.Read<int>(address);
}

void WriteInt(uintptr_t address, int value) {
	mem.Write<int>(address, value);
}