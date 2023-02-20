#pragma once
#include "../../OrbisUtil/include/Trampoline.h"
#include "PCH.h"

namespace Hooks
{
	extern Trampoline::Trampoline*	g_trampoline;
	extern Relocation<uintptr_t> sceGnmSubmitAndFlipCommandBuffersPLTAddress;
	
	void StoreHooks();
	void ApplyHook();
	void RevertHooks();

	static inline void CreateHooks() { StoreHooks(); ApplyHook(); }
}