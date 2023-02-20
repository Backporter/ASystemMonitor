#include "../../OrbisUtil/include/Logger.h"
#include "../../OrbisUtil/include/FileSystem.h"

#include "../../OrbisUtil/include/RelocationManager.h"
#include "../../OrbisUtil/include/Macro.h"

#include "../../CSEL/runetime/Internal/Interfaces/MessagingInterface/MessagingInterface.h"
#include "../../CSEL/runetime/Internal/Interfaces/SerializationInterface/SerializationInterface.h"
#include "../../CSEL/runetime/Internal/Interfaces/TrampolineInterface/TrampolineInterface.h"

#include "../../CSEL/runetime/Internal/Plugin/PluginLoadInfo.h"
#include "../../CSEL/runetime/Internal/Plugin/PluginInfo.h"
#include "../../CSEL/runetime/Internal/Plugin/API.h"

#include "EventManger.h"
#include "ASystemMonitor.h"
#include "Settings.h"
#include "Hook.h"

static Log::Log	g_log;

EXPORT int module_start(size_t argc, const void* argv) { RelocationManager::RelocationManager(); return 0; }
EXPORT int module_stop(size_t argc, const void* argv) { return 0; }

void PluginMessager(Interface::MessagingInterface::Message* MessageInfo)
{
	switch (MessageInfo->m_type)
	{
	case Interface::MessagingInterface::Message::kType::DataLoad:
		Events::ASystemMonitorEventHandler::Register();
		ASystemMonitor::Register();
		break;
	case Interface::MessagingInterface::Message::kType::NewGame:
	case Interface::MessagingInterface::Message::kType::Loaded:
		ASystemMonitor::Show();
		break;
	case Interface::MessagingInterface::Message::kType::MAIN_LOADED:
		Hooks::CreateHooks();
		break;
	default:
		break;
	}
}

// 
EXPORT bool Query(Interface::QueryInterface* a_interface, PluginInfo* a_plugin)
{
	if (!a_interface || !a_plugin)
		return false;

	/* Set Plugin INFO and create a log for use */
	a_plugin->SetPluginName("ASystemMonitor");
	a_plugin->SetPluginVersion(1);

	g_log.OpenRelitive(OrbisFileSystem::Download, "OSEL/Plugins/ASystemMonitor/ASystemMonitor.log");

	return true;
}

EXPORT bool Load(Interface::QueryInterface* a_interface)
{
	if (!a_interface)
		return false;

	g_log.Write("ASystemMonitor loaded!");
	g_log.Close();

	Settings::Settings::Singleton()->Load();
	
	API::initialize(a_interface);
	API::AllocateTrampoline(128);

	auto messaging = API::GetMessagingInterface();
	if (messaging)
	{
		messaging->RegisterPluginCallback(API::GetPluginHandle(), "SELF", PluginMessager);
	}

	return true;
}

EXPORT bool Revert()
{
	return true;
}