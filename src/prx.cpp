#include "API.h"

#include "../../OrbisUtil/include/Logger.h"
#include "../../OrbisUtil/include/FileSystem.h"
#include "../../OrbisUtil/include/Trampoline.h"
#include "../../OrbisUtil/include/RelocationManager.h"
#include "../../OrbisUtil/include/INIHandler.h"

#include "Settings.h"
#include "Hook.h"

EXPORT int module_start(size_t argc, const void* argv)
{
	RelocationManager::RelocationManager();
	return 0;
}

EXPORT int module_stop(size_t argc, const void* argv)
{
	return 0;
}

EXPORT void PluginInit(PluginInfo* Out)
{
	/* Set Plugin INFO and create a log for use */
	Out->Name = "ASystemMonitor";
	Out->_version.INTVersion = 1;
	Out->VersionType = _PluginInfo::Integer;

	Log::Log::GetSingleton()->OpenRelitive(OrbisFileSystem::Download, "ASystemMonitor/ASystemMonitor.log");

	/* store the function for use later */
	API::PushPluginAPI = Out->_PushPluginAPI;

	assert(Trampoline::g_Trampoline.SystemAllocate());
}

EXPORT void PluginStart()
{
	Settings::Settings::Singleton()->Load();
	Hooks::ApplyHook();

	Log::Log::GetSingleton()->Write("ASystemMonitor Loaded");
	Log::Log::GetSingleton()->Close();
}
