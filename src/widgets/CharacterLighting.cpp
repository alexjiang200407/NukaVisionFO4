#include "widgets/CharacterLighting.h"

ImGui::Widget::CharacterLighting::CharacterLighting():
	fill(REL::Relocation<float*>{ RELOCATION_ID(511271, 0) }.get()),
	rim(REL::Relocation<float*>{ RELOCATION_ID(1192770, 0) }.get()),
	enabled(REL::Relocation<bool*>{ RELOCATION_ID(795494, 0) }.get())
{
	logger::info("Installing character lighting hook 0x{:x} 0x{:x} 0x{:x}", uintptr_t(fill.GetValue()), uintptr_t(rim.GetValue()), uintptr_t(enabled.GetValue()));
}

void ImGui::Widget::CharacterLighting::DoFrame()
{
	Text("Character Light");
	Checkbox("Use default", &useDefault);

	BeginDisabled(useDefault);
	Checkbox("Enabled", enabled.GetValue());
	SliderFloat("Fill Light", fill.GetValue(), 0.0f, 0.3f, "%.3f");
	SliderFloat("Rim Light", rim.GetValue(), 0.0f, 0.3f, "%.3f");
	EndDisabled();

	if (useDefault)
	{
		fill.ResetToDefault();
		rim.ResetToDefault();
		enabled.ResetToDefault();
	}
}
