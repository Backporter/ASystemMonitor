#include "ASystemMonitor.h"

ASystemMonitor::ASystemMonitor()
{
	auto ScaleformManger = ConsoleRE::BSScaleformManager::GetSingleton();
	
	depthPriority = 0;
	inputContext = 0;

	menuFlags |= ConsoleRE::UI_MENU_FLAGS::kAlwaysOpen;
	menuFlags |= ConsoleRE::UI_MENU_FLAGS::kRequiresUpdate;
	menuFlags |= ConsoleRE::UI_MENU_FLAGS::kAllowSaving;

	if (Movie)
	{
		Movie->SetMouseCursorCount(0);
	}

	ScaleformManger->LoadMovieEx(this, ASystemMonitor::MENU_NAME, [](ConsoleRE::GFxMovieDefImpl* a_def) -> void { });
	
	util = FrameUtil::Tracker::GetSingleton();
}

void ASystemMonitor::Register()
{
	auto ui = ConsoleRE::UI::GetSingleton();
	if (ui) 
	{
		ui->RegisterMenu(MENU_NAME, Creator);
		ASystemMonitor::Show();
	}
}

void ASystemMonitor::Show()
{
	auto msgQ = ConsoleRE::UIMessageQueue::GetSingleton();
	if (msgQ) 
	{
		msgQ->AddMessageToQueue(ASystemMonitor::MENU_NAME, ConsoleRE::UI_MESSAGE_TYPE::kShow, nullptr);
	}
}

void ASystemMonitor::Hide()
{
	auto msgQ = ConsoleRE::UIMessageQueue::GetSingleton();
	if (msgQ) 
	{
		msgQ->AddMessageToQueue(ASystemMonitor::MENU_NAME, ConsoleRE::UI_MESSAGE_TYPE::kHide, nullptr);
	}
}

void ASystemMonitor::ToggleVisibility(bool mode)
{
	auto ui = ConsoleRE::UI::GetSingleton();
	if (!ui)
		return;

	auto overlayMenu = ui->GetMenu(&ASystemMonitorBS);
	if (!overlayMenu || !overlayMenu->Movie)
		return;

	overlayMenu->Movie->SetVisible(mode);
}

void ASystemMonitor::Update()
{
	ConsoleRE::IMenu* asystemmonitor = ConsoleRE::UI::GetMenu(&ASystemMonitorBS);
	if (!asystemmonitor || !asystemmonitor->Movie)
		return;
	
	if (true)
	{
		if (!IsSet)
		{
			if (asystemmonitor->Movie->GetVariable(SetFrameRateHUDString, "FrameRateHUDString"))
			{
				IsSet = true;
			}
		}
		

		if (IsSet)
		{
			SetFrameRateHUDString.SetText(FrameRateString, false);
		}
		
	}
}

void ASystemMonitor::AdvanceMovie(float f1, uint32_t int1)
{
	sprintf(FrameRateString, "Frame Rate: %f, Frame Delta %f, Frame Time: %f", util->FrameRate, util->FrameDelta, util->FrameTime);

	ASystemMonitor::Update();
	ConsoleRE::IMenu::AdvanceMovie(f1, int1);
}