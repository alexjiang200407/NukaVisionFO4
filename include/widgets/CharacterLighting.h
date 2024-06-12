#pragma once
#include "Widget.h"

namespace ImGui::Widget
{
	class CharacterLighting:
		public Widget
	{
	public:
		CharacterLighting();
		virtual void DoFrame() override;

	private:
		ValueWithDefault<float> fill;
		ValueWithDefault<float> rim;
		ValueWithDefault<bool> enabled;
		bool useDefault;
	};
}
