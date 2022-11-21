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
		}

		return ConsoleRE::BSEventNotifyControl::BST_Continue;
	}
}