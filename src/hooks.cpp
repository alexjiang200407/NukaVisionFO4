#include "hooks.h"

void NV::Hooks::CreateD3DAndSwapChain::thunk()
{
	logger::info("Create D3D Device");
	func();
}

void NV::Hooks::Install()
{
	{
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(224250, 0), 0x114 }; // BSGraphics::InitD3D
		stl::write_thunk_call<CreateD3DAndSwapChain>(target.address());
		logger::info("Writing CreateD3DAndSwapChain hook to address 0x{:x}", target.address());
	}

	{
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(514993, 0) };  // RegisterWindowClassEx
		stl::write_vfunc<WndProc>(target, 0);
		logger::info("Writing RegisterWindowClassExA hook to address 0x{:x}", target.address());		
	}

	//{
	//	REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(67315, 68617), OFFSET(0x7B, 0x7B) };
	//	stl::write_thunk_call<SendInputEvent>(target.address());
	//}

}

ATOM __stdcall NV::Hooks::WndProc::thunk(const WNDCLASSEXA* wnd)
{
	logger::info("Register window class");

	WNDCLASSEXA tmp = *wnd;

	prevWndProc = wnd->lpfnWndProc;
	tmp.lpfnWndProc = WndProcHandler;

	return func(&tmp);
}

inline LRESULT __stdcall NV::Hooks::WndProc::WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return prevWndProc(hWnd, msg, wParam, lParam);
}
