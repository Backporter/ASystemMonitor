#include "../../OrbisUtil/include/Logger.h"
#include "../../OrbisUtil/include/FileSystem.h"
#include "../../OrbisUtil/include/Trampoline.h"
#include "../../OrbisUtil/include/RelocationManager.h"
#include "../../OrbisUtil/include/Macro.h"

#include "../../CSEL/runetime/Internal/Interfaces/MessagingInterface.h"
#include "../../CSEL/runetime/Internal/Plugin.h"

#include "EventManger.h"
#include "ASystemMonitor.h"
#include "Settings.h"
#include "Hook.h"

static Log::Log							g_log;
static size_t							g_pluginHandle   = -1;
static const API::MessagingInterface*	g_messaging		 = nullptr;
static const API::QueryInterface*		g_QueryInterface = nullptr;

EXPORT int module_start(size_t argc, const void* argv) { RelocationManager::RelocationManager(); return 0; }
EXPORT int module_stop(size_t argc, const void* argv) { return 0; }

void PluginMessager(API::MessagingInterface::Message* MessageInfo)
{
	switch (MessageInfo->m_type)
	{
	case API::MessagingInterface::Message::kType::DataLoad:
		Events::ASystemMonitorEventHandler::Register();
		ASystemMonitor::Register();
		break;
	case API::MessagingInterface::Message::kType::NewGame:
	case API::MessagingInterface::Message::kType::Loaded:
		ASystemMonitor::Show();
		break;
	case API::MessagingInterface::Message::kType::MAIN_LOADED:
		Hooks::CreateHooks();
		break;
	default:
		break;
	}
}

// 
EXPORT bool Query(const API::QueryInterface* a_interface, API::PluginInfo* a_plugin)
{
	if (!a_interface || !a_plugin)
		return false;

	/* Set Plugin INFO and create a log for use */
	a_plugin->SetPluginName("ASystemMonitor");
	a_plugin->SetPluginVersion(1);

	g_log.OpenRelitive(OrbisFileSystem::Download, "ASystemMonitor/ASystemMonitor.log");

	return true;
}

EXPORT bool Load(const API::QueryInterface* a_interface)
{
	if (!a_interface)
		return false;

	g_QueryInterface = a_interface;
	g_log.Write("ASystemMonitor loaded!");
	g_log.Close();

	assert(Trampoline::g_Trampoline.SystemAllocate());
	Settings::Settings::Singleton()->Load();
	
	const auto QueryFunc = a_interface->GetQueryFunc();
	if (QueryFunc)
	{
		g_pluginHandle = QueryFunc();
	}

	const auto queryInterfacefunc = a_interface->GetQueryInterfaceFunc();
	if (queryInterfacefunc)
		g_messaging = (API::MessagingInterface*)queryInterfacefunc(API::MessagingInterface::TypeID);

	if (g_messaging)
	{
		auto qu = g_messaging->GetInterfaceCallbackRegister();
		if (qu)
			qu(g_pluginHandle, "SELF", PluginMessager);
	}

	return true;
}

EXPORT bool Revert()
{
	Hooks::RevertHooks();
	Events::ASystemMonitorEventHandler::Unregister();
}