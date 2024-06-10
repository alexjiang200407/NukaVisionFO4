#include "UI.h"

void ImGui::UI::DoFrame()
{
	if (IsKeyPressed(ImGuiKey_End))
	{
		hidden = !hidden;
	}

	if (!hidden)
	{
		ShowDemoWindow();
	}
}
