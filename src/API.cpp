#include "API.h"

#include "EventManger.h"
#include "ASystemMonitor.h"

namespace API
{
	void(*PushPluginAPI)(int API, void* FN, ...);

	void PluginMessager(PluginMessage* MessageInfo)
	{
		switch (MessageInfo->Type)
		{
		case PluginMessage::DataLoad:
			Events::ASystemMonitorEventHandler::Register();
			ASystemMonitor::Register();
			break;
		case PluginMessage::NewGame:
			ASystemMonitor::Show();
			break;
		case PluginMessage::Loaded:
			ASystemMonitor::Show();
			break;
		default:
			break;
		}
	}
}