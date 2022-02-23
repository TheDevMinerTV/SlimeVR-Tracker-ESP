#ifndef LOGGING_LOGGER_H

#include "Level.h"
#include <Arduino.h>

namespace SlimeVR
{
  namespace Logging
  {
    class Logger
    {
    public:
      Logger(const char *prefix) : m_Prefix(prefix){};

      void debug(const char *str, ...);
      void info(const char *str, ...);
      void warn(const char *str, ...);
      void error(const char *str, ...);
      void fatal(const char *str, ...);

    private:
      void log(Level level, const char *str, va_list args);

      const char *m_Prefix;
    };
  }
}

#define LOGGING_LOGGER_H
#endif