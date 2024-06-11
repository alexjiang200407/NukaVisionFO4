#pragma once
#include "ImGuiElement.h"


namespace ImGui
{
	class UI : public ImGuiElement
	{
	public:
		virtual void DoFrame() override;


		bool IsHidden() const;

		void ToggleVisibility();
	private:
		bool hidden = true;
	};

}
