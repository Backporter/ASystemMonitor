#include "ASystemMonitor.h"

bool IsSet = false;
FrameUtil::Tracker* util = nullptr;
MemoryUtil::MemoryUsageTracker* memutil = nullptr;

ConsoleRE::GFxValue SetFrameRateHUDString;

ASystemMonitor::ASystemMonitor()
{
	auto ScaleformManger = ConsoleRE::BSScaleformManager::GetSingleton();
	
	depthPriority = 0;
	inputContext = 0;

	menuFlags |= ConsoleRE::UI_MENU_FLAGS::kAlwaysOpen;
	menuFlags |= ConsoleRE::UI_MENU_FLAGS::kRequiresUpdate;
	menuFlags |= ConsoleRE::UI_MENU_FLAGS::kAllowSaving;

	if (uiMovie)
	{
		uiMovie->SetMouseCursorCount(0);
	}

	ScaleformManger->LoadMovieEx(this, ASystemMonitor::MENU_NAME, [](ConsoleRE::GFxMovieDefImpl* a_def) -> void { });
	
	util = FrameUtil::Tracker::GetSingleton();
	memutil = MemoryUtil::MemoryUsageTracker::GetSingleton();
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
	if (!overlayMenu || !overlayMenu->uiMovie)
		return;

	overlayMenu->uiMovie->SetVisible(mode);
}

void ASystemMonitor::Update()
{
	ConsoleRE::IMenu* asystemmonitor = ConsoleRE::UI::GetMenu(&ASystemMonitorBS);
	if (!asystemmonitor || !asystemmonitor->uiMovie)
		return;
	
	if (true)
	{
		if (!IsSet)
		{
			if (asystemmonitor->uiMovie->GetVariable(&SetFrameRateHUDString, "FrameRateHUDString"))
			{
				IsSet = true;
			}
		}
		

		if (IsSet)
		{
			auto sing = Settings::Settings::Singleton();
			ConsoleRE::GFxValue x = sing->m_options._x;
			ConsoleRE::GFxValue y = sing->m_options._y;
			ConsoleRE::GFxValue w = sing->m_options._w;
			ConsoleRE::GFxValue h = sing->m_options._h;

			ConsoleRE::GFxValue textColor = sing->m_options._textColor;
			ConsoleRE::GFxValue Size = sing->m_options._Size;

			SetFrameRateHUDString.SetMember("_x", &x);
			SetFrameRateHUDString.SetMember("_y", &y);
			SetFrameRateHUDString.SetMember("_w", &w);
			SetFrameRateHUDString.SetMember("_h", &h);
			SetFrameRateHUDString.SetMember("textColor", &textColor);
		 // SetFrameRateHUDString.SetMember("Size", &Size);

			SetFrameRateHUDString.SetText(FrameRateString, false);
		}
		
	}

}

void ASystemMonitor::AdvanceMovie(float f1, uint32_t int1)
{
	sprintf(FrameRateString, "Frame Rate: %f, Frame Delta %f, Frame Time: %f, Memory Usage %d/%d", util->FrameRate, util->FrameDelta, util->FrameTime, memutil->stats.currentInuseSize, memutil->stats.maxSystemSize);
	ASystemMonitor::Update();
	ConsoleRE::IMenu::AdvanceMovie(f1, int1);
}