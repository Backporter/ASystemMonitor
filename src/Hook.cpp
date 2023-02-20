#include "Hook.h"

#include "../../CSEL/runetime/Internal/Plugin/API.h"

#if __ORBIS__
#include <gnm.h>
#define submitAndFlipCommandBuffers sce::Gnm::submitAndFlipCommandBuffers
#elif __OPENORBIS__
#include <orbis/GnmDriver.h>
#define submitAndFlipCommandBuffers submitAndFlipCommandBuffers
#endif

namespace Hooks
{
	int8_t orginalBytes[6] { 0 };

	Relocation<uintptr_t> sceGnmSubmitAndFlipCommandBuffersPLTAddress("sceGnmSubmitAndFlipCommandBuffers:PLT", 0x1717448);

	int32_t submitAndFlipCommandBuffersHook(uint32_t count, void *dcbGpuAddrs[], uint32_t *dcbSizesInBytes, void *ccbGpuAddrs[], uint32_t *ccbSizesInBytes, uint32_t videoOutHandle, uint32_t displayBufferIndex, uint32_t flipMode, int64_t flipArg)
	{
		auto ret = submitAndFlipCommandBuffers(count, dcbGpuAddrs, dcbSizesInBytes, ccbGpuAddrs, ccbSizesInBytes, videoOutHandle, displayBufferIndex, flipMode, flipArg);
		FrameUtil::Tracker::GetSingleton()->Update();
		MemoryUtil::MemoryUsageTracker::GetSingleton()->Update();
		return ret;
	}

	void StoreHooks()
	{
		OrbisMemoryHandler::ReadBuffer(orginalBytes, sceGnmSubmitAndFlipCommandBuffersPLTAddress, 6);
	}

	void ApplyHook()
	{
		API::GetTrampoline().WriteJMP<6>(sceGnmSubmitAndFlipCommandBuffersPLTAddress, (uintptr_t)submitAndFlipCommandBuffersHook);
	}

	void RevertHooks()
	{
		OrbisMemoryHandler::WriteBuffer(sceGnmSubmitAndFlipCommandBuffersPLTAddress, orginalBytes, 6);
	}
}