#pragma once
#include "../ImGuiElement.h"

namespace ImGui::Widget
{
	template<typename T>
	class ValueWithDefault
	{
	public:
		ValueWithDefault(T* val):
			valueAndDefault(std::make_pair(val, *val))
		{}

		T GetDefault() const 
		{
			return valueAndDefault.second;
		}

		T* GetValue() const
		{
			return valueAndDefault.first;
		}

		void ResetToDefault()
		{
			*valueAndDefault.first = GetDefault();
		}
	private:
		std::pair<T*, T> valueAndDefault;
	};


	class Widget :
		public ImGuiElement
	{
	};
}
