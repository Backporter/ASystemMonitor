#include "ASystemMonitor.h"

ASystemMonitor::ASystemMonitor()
{
	auto ScaleformManger = ConsoleRE::GFxLoader::GetSingleton();
	
	this->menuFlags |= ConsoleRE::UI_MENU_FLAGS::kAlwaysOpen;
	this->menuFlags |= ConsoleRE::UI_MENU_FLAGS::kRequiresUpdate;
	this->menuFlags |= ConsoleRE::UI_MENU_FLAGS::kAllowSaving;

	if (this->Movie)
	{
		Movie->SetMouseCursorCount(0);
	}

	ScaleformManger->LoadMovieEx(this, ASystemMonitor::MENU_NAME, [](ConsoleRE::GFxMovieDefImpl* a_def) -> void { });
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

// FrameRateHUDString
void ASystemMonitor::Update()
{
	ConsoleRE::IMenu* asystemmonitor = ConsoleRE::UI::GetMenu(&ASystemMonitorBS);
	if (!asystemmonitor || !asystemmonitor->Movie)
		return;
	
	if (true)
	{
		// ApplyLayout(asystemmonitor);
		
		ConsoleRE::GFxValue fake_framerate("Frame Rate: 59.96"); // static_cast<double>(59.96));
		ConsoleRE::GFxValue textbox;

		if (asystemmonitor->Movie->GetVariable(textbox, "TextField0"))
		{
			textbox.SetText("Frame Rate: 59.96", false);
		}
	}
}

void ASystemMonitor::ApplyLayout(ConsoleRE::IMenu* ASystemMonitor)
{
	if (!ASystemMonitor || !ASystemMonitor->Movie)
		return;

	ConsoleRE::GFxValue widget_xpos     = Settings::Settings::Singleton()->m_options.widget_xpos;
	ConsoleRE::GFxValue widget_ypos     = Settings::Settings::Singleton()->m_options.widget_ypos;
	ConsoleRE::GFxValue widget_rotation = Settings::Settings::Singleton()->m_options.widget_rotation;
	ConsoleRE::GFxValue widget_xscale   = Settings::Settings::Singleton()->m_options.widget_xscale;
	ConsoleRE::GFxValue widget_yscale   = Settings::Settings::Singleton()->m_options.widget_yscale;

	ConsoleRE::GFxValue posArray[5]{ widget_xpos, widget_ypos, widget_rotation, widget_xscale, widget_yscale };
	ASystemMonitor->Movie->Invoke("monitor.setLocation", nullptr, posArray, 5);
}

void ASystemMonitor::AdvanceMovie(float f1, uint32_t int1)
{
	ASystemMonitor::Update();
	ConsoleRE::IMenu::AdvanceMovie(f1, int1);
}