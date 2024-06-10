#pragma once
#include "ImGuiRenderer.h"
#include "WindowsMessageMap.h"
#include "UI.h"

namespace Plugin
{
	class WindowSubclass
	{
	public:
		static void Init();

	private:
		WindowSubclass() = default;

	private:
		LRESULT ProcessMessage(HWND hWnd, INT uMsg, WPARAM wParam, LPARAM lParam);

		static LRESULT CALLBACK s_SubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
			LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

	private:
		struct RegisterClassExHook
		{
			static void Install();
			static LRESULT s_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			static void thunk(const WNDCLASSEXA* wnd);
			static inline REL::Relocation<decltype(thunk)> func;
		};

	private:
		WindowsMessageMap msgMap;
		ImGui::ImGuiRenderer imgui;
		static inline WNDPROC prevWndProc;
		ImGui::UI* ui = nullptr;
	};
}
