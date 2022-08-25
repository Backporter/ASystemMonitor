#pragma once

#include "../../OrbisUtil/include/Macro.h"
#include "../../CSEL/runetime/source/P/PluginAPI.h"

namespace API
{
	extern void (*PushPluginAPI)(int API, void* FN, ...);

	EXPORT void PluginMessager(PluginMessage* MessageInfo);
}