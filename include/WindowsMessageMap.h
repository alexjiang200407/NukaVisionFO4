#pragma once


namespace NV
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
