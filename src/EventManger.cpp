#include "EventManger.h"

namespace Events
{
	ConsoleRE::BSEventNotifyControl ASystemMonitorEventHandler::ProcessEvent(ConsoleRE::MenuOpenCloseEvent* a_event, ConsoleRE::BSTEventSource<ConsoleRE::MenuOpenCloseEvent>* a_source)
	{
		if (a_event)
		{
			auto menustrings = ConsoleRE::UIMenuStrings::GetSingleton();
			if (a_event->Name == menustrings->hudMenu)
			{
				if (a_event->IsOpening)
				{
					ASystemMonitor::Show();
				}
				else
				{
					ASystemMonitor::Hide();
				}
			}
			
			else if (a_event->Name == menustrings->raceSexMenu && !a_event->IsOpening)
			{
				ASystemMonitor::Show();
			}
			
			else if (a_event->Name == menustrings->loadingMenu && !a_event->IsOpening)
			{
				ASystemMonitor::Show();
			}
			
			if (a_event->Name == menustrings->containerMenu && a_event->IsOpening)
			{
				ASystemMonitor::Hide();
			}
			
			if (a_event->Name == menustrings->journalMenu)
			{
				Settings::Settings::Singleton()->Load();
			}
		}

		auto controlMap = ConsoleRE::ControlMap::GetSingleton();
		if (controlMap)
		{
			auto& priorityStack = controlMap->contextPriorityStack;
			if (priorityStack.empty() || (priorityStack.back() != 0 && priorityStack.back() != 6 && priorityStack.back() != 2))
			{
				ASystemMonitor::ToggleVisibility(false);
			}
			else
			{
				ASystemMonitor::ToggleVisibility(true);
			}
		}

		return ConsoleRE::BSEventNotifyControl::BST_Continue;
	}
}