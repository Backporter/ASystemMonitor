#pragma once

#include "../../OrbisUtil/include/MessageHandler.h"
#include "../../OrbisUtil/include/FileSystem.h"
#include "../../OrbisUtil/Third-Party/benhoyt/1.0/INIReader.h"

namespace Settings
{
	struct Options
	{
	public:
		bool bShowFrameRate;
		bool bShowFrameTime;
		bool bShowFrameDelta;
		bool pad04;

		float widget_xpos;     //  { 961.0f  };
		float widget_ypos;     //  { 1040.0f };
		float widget_rotation; //  { 0.0f    };
		float widget_xscale;   //  { 75.0f   };
		float widget_yscale;   //  { 75.0f   };
	};

	class Settings
	{
	public:
		Settings() { };
		~Settings() { };

		static Settings* Singleton()
		{
			static Settings singleton;
			return &singleton;
		}

		// PRIOR = MIRA -> DATA -> APP0

		static const char* GetINIPath()
		{
			constexpr const char* MIRA = "/_mira/ASystemMonitor.ini";
			constexpr const char* DATA = "/data/CSEL/data/ASystemMonitor.ini";
			constexpr const char* APP0 = "/app0/data/CSEL/ASystemMonitor.ini";
			
			if (OrbisFileSystem::PathExists(OrbisFileSystem::Full, MIRA, false))
				return MIRA;

			if (OrbisFileSystem::PathExists(OrbisFileSystem::Full, DATA, false))
				return DATA;

			if (OrbisFileSystem::PathExists(OrbisFileSystem::Full, APP0, false))
				return APP0;
			
			return NULL;
		}

		bool Load()
		{
			const char* path = GetINIPath();
			if (path)
			{
				m_ini = INIReader(path);
				if (m_ini.ParseError() == 0)
				{
					// TBA

					// m_options.bShowFrameRate  = m_ini.GetBoolean("Settings", "bShowFrameRate", true);
					// m_options.bShowFrameTime  = m_ini.GetBoolean("Settings", "bShowFrameTime", true);
					// m_options.bShowFrameDelta = m_ini.GetBoolean("Settings", "bShowFrameDelta", true);

					m_options.widget_xpos     = m_ini.GetFloat("POS", "X",  961.0f  );
					m_options.widget_ypos     = m_ini.GetFloat("POS", "Y",  1040.0f );
					m_options.widget_rotation = m_ini.GetFloat("POS", "R",  0.0f    );
					m_options.widget_xscale   = m_ini.GetFloat("POS", "XS", 75.0f   );
					m_options.widget_yscale   = m_ini.GetFloat("POS", "YS", 75.0f   );

					return true;
				}
			}
			else
			{
				m_options.widget_xpos = 961.0f;
				m_options.widget_ypos = 1040.0f;
				m_options.widget_rotation = 0.0f;
				m_options.widget_xscale = 75.0f;
				m_options.widget_yscale = 75.0f;

				return false;
			}

			return false;
		}

	public:
		INIReader	m_ini;
		Options		m_options;
	};
}