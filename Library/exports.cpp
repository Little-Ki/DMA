
#include <unordered_map>
#include "exports.h"
#include "dma.h"

std::unordered_map<uint32_t, DMA> dmas;

uint32_t current_id = 0;

DMA* findDMA(uint32_t dma_id) {
	if (dmas.find(dma_id) == dmas.end())
		return nullptr;
	return &dmas[dma_id];
}

uint32_t CreateDMA()
{
	auto id = current_id++;
	dmas[id] = DMA();
	return id;
}

DLL_EXPORT bool InitializeDMA(uint32_t dma_id)
{
	auto dma = findDMA(dma_id);
	return dma ? dma->initialize() : false;
}

DLL_EXPORT void CloseDMA(uint32_t dma_id)
{
	auto dma = findDMA(dma_id);
	if (dma)
		dma->close();
	dmas.erase(dma_id);
}

DLL_EXPORT bool OpenProcess(uint32_t dma_id, const wchar_t* wname)
{
	auto dma = findDMA(dma_id);
	return dma ? dma->openProcess(wname) : false;
}

DLL_EXPORT float ReadFloat(uint32_t dma_id, uintptr_t address)
{
	auto dma = findDMA(dma_id);
	return dma ? dma->read<float>(address) : 0.0f;
}

DLL_EXPORT int ReadInt(uint32_t dma_id, uintptr_t address)
{
	auto dma = findDMA(dma_id);
	return dma ? dma->read<int>(address) : 0;
}

DLL_EXPORT bool WriteFloat(uint32_t dma_id, uintptr_t address, float value)
{
	auto dma = findDMA(dma_id);
	return dma ? dma->write<float>(address, value) : false;
}

DLL_EXPORT bool WriteInt(uint32_t dma_id, uintptr_t address, int value)
{
	auto dma = findDMA(dma_id);
	return dma ? dma->write<int>(address, value) : false;
}
