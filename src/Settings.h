#pragma once

#include "../../OrbisUtil/include/MessageHandler.h"
#include "../../OrbisUtil/include/FileSystem.h"
#include "../../OrbisUtil/Third-Party/benhoyt/1.0/INIReader.h"

namespace Settings
{
	struct Options
	{
	public:
		bool bShowFrameRate{ true };
		bool bShowFrameDelta{ true };
		bool bShowFrameTime{ true };
		bool bpad;

		// 
		double _x		  { 0.0			};
		double _y		  { 0.0			};
		double _w		  { 1920.0		};
		double _h		  { 60.0		};
		double _Size	  { 19.0		};
		double _textColor { 0xFFFFFF	};
		double _rot		  { 0.0			};
		double _xScale	  { 100.0		};
		double _yScale	  { 100.0		};
	};

	class Settings
	{
	public:
		Settings() {}
		~Settings() {}

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
			{
				return MIRA;
			}

			if (OrbisFileSystem::PathExists(OrbisFileSystem::Full, DATA, false))
			{
				return DATA;
			}

			if (OrbisFileSystem::PathExists(OrbisFileSystem::Full, APP0, false))
			{
				return APP0;
			}
			
			return NULL;
		}

		bool Load()
		{
			const char* path = GetINIPath();
			if (path)
			{
				m_ini = INIReader(path);
				if (!m_ini.ParseError())
				{
					m_options._x			= m_ini.GetReal("Display", "_x", 0.0);
					m_options._y			= m_ini.GetReal("Display", "_y", 0.0);
					m_options._w			= m_ini.GetReal("Display", "_w", 1920.0);
					m_options._h			= m_ini.GetReal("Display", "_h", 60.0);
					m_options._Size			= m_ini.GetReal("Display", "Size", 19.0);
					m_options._textColor	= m_ini.GetReal("Display", "textColor", 0xFFFFFF);
					m_options._rot			= m_ini.GetReal("Display", "_rot", 0.0);
					m_options._xScale		= m_ini.GetReal("Display", "_xScale", 100.0);
					m_options._yScale		= m_ini.GetReal("Display", "_yScale", 100.0);

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