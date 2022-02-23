#include "Level.h"

namespace SlimeVR
{
	namespace Logging
	{
		const char *levelToString(Level level)
		{
			switch (level)
			{
			case DEBUG:
				return "DEBUG";
			case INFO:
				return "INFO";
			case WARN:
				return "WARN";
			case ERROR:
				return "ERROR";
			case FATAL:
				return "FATAL";
			default:
				return "UNKNOWN";
			}
		}
	}
}
