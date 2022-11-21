#pragma once
#include "PCH.h"

namespace Hooks
{
	extern Relocation<uintptr_t> sceGnmSubmitAndFlipCommandBuffersPLTAddress;
	
	void StoreHooks();
	void ApplyHook();
	void RevertHooks();

	static inline void CreateHooks() { StoreHooks(); ApplyHook(); }
}