#pragma once

namespace ImGui
{
	class ImGuiElement
	{
	public:
		virtual void DoFrame() = 0;
	};
}
