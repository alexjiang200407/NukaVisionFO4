#include "UI.h"

void ImGui::UI::DoFrame()
{
	if (IsKeyPressed(ImGuiKey_End))
		ToggleVisibility();

	if (!hidden)
	{
		//ShowDemoWindow();
		Begin("##NukaVisionControlPanel");

		Text("Hello World!");

		End();
	}
}



bool ImGui::UI::IsHidden() const
{
	return hidden;
}

void ImGui::UI::ToggleVisibility()
{
	auto& io = GetIO();
	if (hidden)
	{
		io.MouseDrawCursor = true;
		hidden = false;
	}
	else
	{
		io.MouseDrawCursor = false;
		hidden = true;
	}
}
