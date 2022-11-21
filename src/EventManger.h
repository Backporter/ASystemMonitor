#pragma once

#include "PCH.h"
#include "ASystemMonitor.h"

namespace Events
{
	class ASystemMonitorEventHandler : public ConsoleRE::BSTEventSink<ConsoleRE::MenuOpenCloseEvent>
	{
	public:		
		static ASystemMonitorEventHandler* GetSingleton()
		{
			static ASystemMonitorEventHandler singleton;
			return &singleton;
		}

		virtual ConsoleRE::BSEventNotifyControl ProcessEvent(ConsoleRE::MenuOpenCloseEvent*, ConsoleRE::BSTEventSource<ConsoleRE::MenuOpenCloseEvent>*);

		static void Register()
		{
			ConsoleRE::UI::GetSingleton()->GetEventSource<ConsoleRE::MenuOpenCloseEvent>()->AddEventSink(ASystemMonitorEventHandler::GetSingleton());
		}

		static void Unregister()
		{
			ConsoleRE::UI::GetSingleton()->GetEventSource<ConsoleRE::MenuOpenCloseEvent>()->RemoveEventSink(ASystemMonitorEventHandler::GetSingleton());
		}
	};
}