#pragma once

#include "Hash/Hash.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
//#include <WinNls.h>

namespace Util
{
	static std::wstring ConvertUtf8ToWide(const std::string& str)
	{
		int cnt = MultiByteToWideChar(65001, 0, str.data(), str.length(), NULL, 0);

		std::wstring s(cnt, 0);
		MultiByteToWideChar(65001, 0, str.data(), str.length(), &s[0], cnt);

		return s;
	}

	template<typename F, typename ... T>
	inline bool CompareGroup(F&& first, T&& ... t)
	{
		return ((first == t) || ...);
	}
}

#define FAILED_TO_HOOK false

#define CREATE_HOOK(name, address, type, callconvo, ...) namespace Hooks \
{ \
	namespace name \
	{ \
		inline Hook::C_Function Func; \
		using FN = type(callconvo*)(__VA_ARGS__); \
		type callconvo Detour(__VA_ARGS__); \
		inline void Initialize() \
		{ \
			XASSERT(Func.Initialize(reinterpret_cast<void*>(address), &Detour) == FAILED_TO_HOOK); \
		} \
	}\
}

#define DEFINE_HOOK(name, type, callconvo, ...) type callconvo Hooks::name::Detour(__VA_ARGS__)