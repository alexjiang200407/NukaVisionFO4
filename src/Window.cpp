#include "window.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Plugin::WindowSubclass::RegisterClassExHook::Install()
{
	REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(514993, 0) };  // RegisterWindowClassEx
	stl::write_vfunc<RegisterClassExHook>(target, 0);
	logger::info("Writing RegisterWindowClassExA hook to address 0x{:x}", target.address());
}

void Plugin::WindowSubclass::RegisterClassExHook::thunk(const WNDCLASSEXA* wnd)
{
	logger::info("Register window class");

	WNDCLASSEXA tmp = *wnd;

	prevWndProc = wnd->lpfnWndProc;
	tmp.lpfnWndProc = s_WndProc;

	return func(&tmp);
}

LRESULT Plugin::WindowSubclass::RegisterClassExHook::s_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static WindowSubclass wnd;

	if (uMsg == WM_CREATE)
	{
		logger::info("Creating window");
		if (SetWindowSubclass(hWnd, WindowSubclass::s_SubclassProc, 0, (DWORD_PTR)&wnd) == FALSE)
		{
			logger::error("FAILED TO SET WINDOW SUBCLASS");
			return prevWndProc(hWnd, uMsg, wParam, lParam);
		}

		wnd.imgui.Init();
		wnd.ui = wnd.imgui.RegisterImGuiElement<ImGui::UI>();
	}

	return prevWndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Plugin::WindowSubclass::s_SubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	WindowSubclass* pWnd = reinterpret_cast<WindowSubclass*>(dwRefData);

	if (!pWnd)
	{
		logger::error("Window not found!!!!");
		return 0;
	}

	return pWnd->ProcessMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT Plugin::WindowSubclass::ProcessMessage(HWND hWnd, INT uMsg, WPARAM wParam, LPARAM lParam)
{
	logger::trace("MSG: {}, wParam: 0x{:x}, lParam: 0x{:x}", msgMap.ToString(uMsg), wParam, lParam);

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return prevWndProc(hWnd, uMsg, wParam, lParam);
}

void Plugin::WindowSubclass::Init()
{
	RegisterClassExHook::Install();
}
