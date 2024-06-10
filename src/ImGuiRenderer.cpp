#include "ImGuiRenderer.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

void ImGui::ImGuiRenderer::D3D11CreateDeviceAndSwapChainHook::Install()
{
	REL::Relocation<std::uintptr_t> target{ REL::ID(254484) };  // D3D11CreateDeviceAndSwapChainHook
	stl::write_vfunc<D3D11CreateDeviceAndSwapChainHook>(target, 0);
	logger::info("Writing D3D11CreateDeviceAndSwapChain hook to address 0x{:x}", target.address());
}

HRESULT ImGui::ImGuiRenderer::D3D11CreateDeviceAndSwapChainHook::thunk(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, IDXGISwapChain** ppSwapChain, ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext)
{
	HRESULT ret = func(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);

	logger::info("Initializing ImGui...");

	if (FAILED(ret))
		return ret;

	std::uintptr_t* vtbl = (std::uintptr_t*)(*ppSwapChain);
	vtbl = (std::uintptr_t*)vtbl[0];

	REL::Relocation<std::uintptr_t> target{ (uintptr_t)vtbl };


	logger::info("Writing PresentHook hook to address 0x{:x}", target.address());
	stl::write_vfunc<PresentHook>(target, 8);

	ImGui::CreateContext();

	HWND hWnd = GetActiveWindow();

	if (!ImGui_ImplWin32_Init(hWnd))
	{
		logger::error("ImGui initialization failed (Win32)");
		return ret;
	}
	if (!ImGui_ImplDX11_Init(*ppDevice, *ppImmediateContext))
	{
		logger::error("ImGui initialization failed (DX11)");
		return ret;
	}

	logger::info("Successfully initialized ImGui...");
	initialized.store(true);

	auto& io = ImGui::GetIO();
	io.ConfigFlags |= (ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_NoMouseCursorChange);
	io.IniFilename = nullptr;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.MouseDrawCursor = true;
	{
		io.ConfigWindowsMoveFromTitleBarOnly = true;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	}

	return ret;
}

void ImGui::ImGuiRenderer::Init()
{
	D3D11CreateDeviceAndSwapChainHook::Install();
}

void ImGui::ImGuiRenderer::UnregisterImGuiElement(ImGuiElement* element)
{
	auto it = elements.find(element);

	if (it != elements.end())
		elements.erase(it);
}

bool ImGui::ImGuiRenderer::isInitialized()
{
	return initialized.load();
}

HRESULT ImGui::ImGuiRenderer::PresentHook::thunk(IDXGISwapChain* a_self, UINT a_syncInterval, UINT a_flags)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	for (const auto& pElement : elements)
		pElement->DoFrame();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return func(a_self, a_syncInterval, a_flags);
}
