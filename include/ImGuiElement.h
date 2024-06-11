#pragma once

namespace ImGui
{
	class ImGuiElement
	{
	public:
		virtual ~ImGuiElement() = default;
		virtual void DoFrame() = 0;
	};
}
