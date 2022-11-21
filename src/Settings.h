#pragma once

#include "../../OrbisUtil/include/MessageHandler.h"
#include "../../OrbisUtil/include/FileSystem.h"
#include "../../OrbisUtil/Third-Party/benhoyt/1.0/INIReader.h"

namespace Settings
{
	struct Options
	{
	public:
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
					return true;
				}
			}
			else
			{
				return false;
			}

			return false;
		}

	public:
		INIReader	m_ini;
		Options		m_options;
	};
}