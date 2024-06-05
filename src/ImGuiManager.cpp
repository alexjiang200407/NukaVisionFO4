#include "ImGuiManager.h"

void NV::ImGuiManager::D3D11CreateDeviceAndSwapChainHook::Install()
{
	REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(254484, 0) };  // D3D11CreateDeviceAndSwapChainHook
	stl::write_vfunc<D3D11CreateDeviceAndSwapChainHook>(target, 0);
	logger::info("Writing D3D11CreateDeviceAndSwapChain hook to address 0x{:x}", target.address());
}

HRESULT NV::ImGuiManager::D3D11CreateDeviceAndSwapChainHook::thunk(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, IDXGISwapChain** ppSwapChain, ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext)
{
	HRESULT ret = func(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);

	logger::info("Initializing ImGui...");

	if (FAILED(ret))
		return ret;

	std::uintptr_t* vtbl = (std::uintptr_t*)(*ppSwapChain);
	vtbl = (std::uintptr_t*)vtbl[0];

	REL::Relocation<std::uintptr_t> target{ (uintptr_t)vtbl };

	stl::write_vfunc<PresentHook>(target, 8);


	//HookFunc(vtbl, 8, (std::uintptr_t)PresentHook, (std::uintptr_t*)&oldFuncs.d3dPresent);

	//auto window = ::GetActiveWindow();

	//::GetWindowRect(window, &oldRect);

	//imgui_menu::Menu::GetSingleton().Init(window, (*ppDevice), (*ppImmediateContext));

	return ret;
}

void NV::ImGuiManager::Init()
{
	ImGuiManager::D3D11CreateDeviceAndSwapChainHook::Install();
}

HRESULT NV::ImGuiManager::PresentHook::thunk(IDXGISwapChain* a_self, UINT a_syncInterval, UINT a_flags)
{
	logger::trace("Present!");
	return func(a_self, a_syncInterval, a_flags);
}
