#pragma once

#include <string>

namespace Imports
{
	typedef bool(*EventHook)(void* pData);

	static HMODULE hUndergroundCoreModule;

	// A wrapper around GetProcAddress so we can get a read-only address of the function export
	const uint32_t GetFunctionAddress(HMODULE hModule, std::string sExportName)
	{
		const uint32_t dwAddress = reinterpret_cast<const uint32_t>(GetProcAddress(hModule, sExportName.c_str()));

		/*if (!dwAddress)
		{
			PrintMessageBox("%s failed to import", sExportName.c_str());
		}*/

		return dwAddress;
	}

	extern "C"
	{
		/*
			Underground Core imports
		*/
		// Registers an event callback
		static void RegisterEventCallback(const char* szEventType, EventHook fpEventCallback)
		{
			((void(__cdecl*)(const char*, EventHook))GetFunctionAddress(hUndergroundCoreModule, "RegisterEventCallback"))(szEventType, fpEventCallback);
		}
	}
}