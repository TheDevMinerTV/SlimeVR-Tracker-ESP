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
      template <typename T>
      void debugArray(const char *str, const T *array, int size)
      {
        logArray(DEBUG, str, array, size);
      }

      void info(const char *str, ...);
      template <typename T>
      void infoArray(const char *str, const T *array, int size)
      {
        logArray(INFO, str, array, size);
      }

      void warn(const char *str, ...);
      template <typename T>
      void warnArray(const char *str, const T *array, int size)
      {
        logArray(WARN, str, array, size);
      }

      void error(const char *str, ...);
      template <typename T>
      void errorArray(const char *str, const T *array, int size)
      {
        logArray(ERROR, str, array, size);
      }

      void fatal(const char *str, ...);
      template <typename T>
      void fatalArray(const char *str, const T *array, int size)
      {
        logArray(FATAL, str, array, size);
      }

    private:
      void log(Level level, const char *str, va_list args);
      template <typename T>
      void logArray(Level level, const char *str, const T *array, int size)
      {
        Serial.printf("[%-5s] [%s] %s", levelToString(level), m_Prefix, str);

        for (size_t i = 0; i < size; i++)
        {
          Serial.print(array[i]);
        }

        Serial.println();
      }

      const char *m_Prefix;
    };
  }
}

#define LOGGING_LOGGER_H
#endif