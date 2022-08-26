#pragma once

#include "PCH.h"
#include "Settings.h"

static ConsoleRE::GFxValue SetFrameRateHUDString;
static bool IsSet{ false };
static char FrameRateString[8192];
static FrameUtil::Tracker* util;

class ASystemMonitor : ConsoleRE::IMenu
{
public:
	static constexpr const char*	MENU_PATH = "ASystemMonitor";
	static constexpr const char*	MENU_NAME = "ASystemMonitor";
	inline static ConsoleRE::BSFixedString ASystemMonitorBS = "ASystemMonitor";

	ASystemMonitor();
	static void Register();
	static void Show();
	static void Hide();
	static void Update();
	static void ToggleVisibility(bool mode);

	static ConsoleRE::IMenu* Creator() { return new ASystemMonitor(); };
	virtual void AdvanceMovie(float f1, uint32_t int1) override;
public:
};