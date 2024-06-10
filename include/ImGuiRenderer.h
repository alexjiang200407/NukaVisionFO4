#pragma once
#include <d3d11.h>
#include "ImGuiElement.h"
#include <set>

namespace ImGui
{
	class ImGuiRenderer
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

		struct ImGuiElementComparator
		{
			using is_transparent = void;

			bool operator()(const std::unique_ptr<ImGuiElement>& lhs, const std::unique_ptr<ImGuiElement>& rhs) const
			{
				return lhs.get() < rhs.get();
			}
			bool operator()(const std::unique_ptr<ImGuiElement>& lhs, const ImGuiElement* rhs) const
			{
				return lhs.get() < rhs;
			}
			bool operator()(const ImGuiElement* lhs, const std::unique_ptr<ImGuiElement>& rhs) const
			{
				return lhs < rhs.get();
			}
		};

	public:
		void Init();

		template<class T>
		T* RegisterImGuiElement()
		{
			return static_cast<T*>(elements.insert(std::make_unique<T>()).first->get());
		};

		void UnregisterImGuiElement(ImGuiElement* element);

		bool isInitialized();
	private:
		static inline std::atomic<bool> initialized;
		static inline std::set<std::unique_ptr<ImGuiElement>, ImGuiElementComparator> elements{};
	};
}
