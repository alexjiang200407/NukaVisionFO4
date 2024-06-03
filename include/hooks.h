#pragma once

namespace NV
{
	class Hooks :
		public Singleton<Hooks>
	{
	private:
		struct WndProc
		{
			static ATOM __stdcall thunk(const WNDCLASSEXA* wnd);
			static inline REL::Relocation<decltype(thunk)> func;
			static inline LRESULT __stdcall WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			static inline WNDPROC prevWndProc;
		};

		struct CreateD3DAndSwapChain
		{
			static void thunk();
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct StopTimer
		{
			static void thunk(std::uint32_t timer);
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct SendInputEvent
		{
			static void thunk(RE::BSTEventSource<RE::InputEvent*>* dispatcher, RE::InputEvent* const* ppEvents);
			static inline REL::Relocation<decltype(thunk)> func;
		};

		public:
			static void Install();

		private:
			std::atomic<bool> installedHooks;
	};
}
