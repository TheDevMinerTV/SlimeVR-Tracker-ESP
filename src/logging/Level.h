#ifndef LOGGING_LEVEL_H

namespace SlimeVR
{
	namespace Logging
	{
		enum Level
		{
			DEBUG = 0,
			INFO = 1,
			WARN = 2,
			ERROR = 3,
			FATAL = 4
		};

		const char *levelToString(Level level);
	}
}

#define LOGGING_LEVEL_H
#endif