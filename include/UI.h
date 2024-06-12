#pragma once
#include "ImGuiElement.h"
#include "widgets/CharacterLighting.h"


namespace ImGui
{
	class UI : public ImGuiElement
	{
	public:
		virtual void DoFrame() override;

		bool IsHidden() const;

		void ToggleVisibility();
	private:
		Widget::CharacterLighting characterLight;
		bool hidden = true;
	};

}
