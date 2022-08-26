#include "Hook.h"

namespace Hooks
{
	Relocation<uintptr_t> sceGnmSubmitAndFlipCommandBuffersPLTAddress("sceGnmSubmitAndFlipCommandBuffers:PLT", 0x1717448);

	int32_t submitAndFlipCommandBuffersHook(uint32_t count, void *dcbGpuAddrs[], uint32_t *dcbSizesInBytes, void *ccbGpuAddrs[], uint32_t *ccbSizesInBytes, uint32_t videoOutHandle, uint32_t displayBufferIndex, uint32_t flipMode, int64_t flipArg)
	{
		auto ret = sce::Gnm::submitAndFlipCommandBuffers(count, dcbGpuAddrs, dcbSizesInBytes, ccbGpuAddrs, ccbSizesInBytes, videoOutHandle, displayBufferIndex, flipMode, flipArg);
		FrameUtil::Tracker::GetSingleton()->Update();
		return ret;
	}

	void ApplyHook()
	{
		Trampoline::g_Trampoline.WriteJMP<6>(sceGnmSubmitAndFlipCommandBuffersPLTAddress, (uintptr_t)submitAndFlipCommandBuffersHook);
	}
}