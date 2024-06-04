#include "hooks.h"
#include "window.h"

void NV::Hooks::CreateD3DAndSwapChain::thunk()
{
	logger::info("Create D3D Device");
	func();
}

void NV::Hooks::Install()
{
	{
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(224250, 0), 0x114 };  // BSGraphics::InitD3D
		stl::write_thunk_call<CreateD3DAndSwapChain>(target.address());
		logger::info("Writing CreateD3DAndSwapChain hook to address 0x{:x}", target.address());
	}
}
