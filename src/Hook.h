#pragma once
#include "PCH.h"

namespace Hooks
{
#if defined(__ORBIS__) || defined(__OPENORBIS__)
#if defined(__ORBIS__)
#include <gnm.h>
#endif
	extern Relocation<uintptr_t> sceGnmSubmitAndFlipCommandBuffersPLTAddress;
#endif

	void ApplyHook();
}