#pragma once
#include "ImGuiElement.h"


namespace ImGui
{
	class UI : public ImGuiElement
	{
	public:
		virtual void DoFrame() override;

	private:
		bool hidden = true;
	};

}
