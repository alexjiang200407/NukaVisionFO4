#pragma once
#include <d3d11.h>

namespace NV
{
	class ImGuiManager
	{
	private:
		struct D3D11CreateDeviceAndSwapChainHook
		{
			static void Install();
			static HRESULT CALLBACK thunk(
				IDXGIAdapter* pAdapter,
				D3D_DRIVER_TYPE DriverType,
				HMODULE Software, UINT Flags,
				const D3D_FEATURE_LEVEL* pFeatureLevels,
				UINT FeatureLevels,
				UINT SDKVersion,
				const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
				IDXGISwapChain** ppSwapChain,
				ID3D11Device** ppDevice,
				D3D_FEATURE_LEVEL* pFeatureLevel,
				ID3D11DeviceContext** ppImmediateContext);

			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct PresentHook
		{
			static HRESULT CALLBACK thunk(IDXGISwapChain* a_self, UINT a_syncInterval, UINT a_flags);
			static inline REL::Relocation<decltype(thunk)> func;
		};

	public:
		static void Init();
	};
}
