#pragma once

#include <string>

namespace Imports
{
	typedef bool(*EventHook)(void* pData);

	enum eEventType
	{
		// Global scope
		EVENT_BEFORE_RENDER2DSTUFF, // Returning false in this callback blocks other callbacks and the default UG code from being executed
		EVENT_AFTER_RENDER2DSTUFF, // Return value from callback is ignored
		EVENT_BEFORE_RENDERSCENE, // Returning false in this callback blocks other callbacks and the default UG code from being executed
		EVENT_AFTER_RENDERSCENE, // Return value from callback is ignored

		// CGame
		EVENT_SHUTDOWNFORRESTART, // Returning false in this callback blocks other callbacks and the default UG code from being executed
		EVENT_BEFORE_PROCESSGAME, // Returning false in this callback blocks other callbacks and the default UG code from being executed
		EVENT_AFTER_PROCESSGAME, // Return value from callback is ignored

		// CTheScripts
		EVENT_STARTTESTSCRIPT, // Returning false in this callback blocks other callbacks and the default UG code from being executed. Fires in CGame::Initialise and in CGame::ReInitGameObjectVariables

		// CPopulation
		EVENT_UPDATEPOPULATION, // Returning false in this callback will make CPopulation::Update never spawn new population (and also blocks other callbacks from being executed). 
								// All callbacks must return true for CPopulation::Update to only spawn population during specific frames. For now, this is only used by GTA: Connected.

		// CPostEffects
		EVENT_INITPOSTEFFECTS, // Returning false in this callback blocks other callbacks and the default UG code from being executed
		EVENT_CLOSEPOSTEFFECTS, // Returning false in this callback blocks other callbacks and the default UG code from being executed

		// CTheCarGenerators
		EVENT_PROCESSCARGENERATORS, // Returning false in this callback blocks other callbacks and CTheCarGenerators::Process being executed

		// CWorld
		EVENT_BEFORE_RENDERFADINGINENTITIES, // Takes place inside RenderScene! Returning false in this callback blocks other callbacks from being executed. The rest of RenderScene will be executed however.
		EVENT_AFTER_RENDERFADINGINENTITIES, // Return value from callback is ignored

		MAX_EVENT_CALLBACKS
	};

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
		static void RegisterEventCallback(eEventType nEventType, EventHook fpEventCallback)
		{
			((void(__cdecl*)(eEventType, EventHook))GetFunctionAddress(hUndergroundCoreModule, "RegisterEventCallback"))(nEventType, fpEventCallback);
		}
	}
}