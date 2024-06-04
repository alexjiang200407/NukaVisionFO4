#pragma once
#include "WindowsMessageMap.h"

namespace NV
{
	class WindowSubclass
	{
	private:
		static LRESULT CALLBACK s_SubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
			LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

		LRESULT ProcessMessage(HWND hWnd, INT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		struct RegisterClassExHook
		{
			static void Install();
			static LRESULT s_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			static void thunk(const WNDCLASSEXA* wnd);
			static inline REL::Relocation<decltype(thunk)> func;
		};

	private:
		WindowsMessageMap msgMap;
		static WNDPROC prevWndProc;
	};
}
