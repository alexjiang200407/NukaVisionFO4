#pragma once


namespace Plugin
{
	class WindowsMessageMap
	{
	public:
		WindowsMessageMap();
		std::string ToString(UINT msg) const;
	private:
		std::unordered_map<DWORD, std::string> map;
	};
}
