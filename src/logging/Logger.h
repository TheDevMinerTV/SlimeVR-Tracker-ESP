/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2022 TheDevMinerTV

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <Arduino.h>

#include "Level.h"
#include "debug.h"

namespace SlimeVR {
    namespace Logging {
        class Logger {
        public:
            Logger(const char* prefix) : m_Prefix(prefix), m_Tag(nullptr){};
            Logger(const char* prefix, const char* tag) : m_Prefix(prefix), m_Tag(nullptr) {
                setTag(tag);
            };

            ~Logger() {
                if (m_Tag != nullptr) {
                    free(m_Tag);
                }
            }

            void setTag(const char* tag);

            void trace(const char* str, ...);
            void debug(const char* str, ...);
            void info(const char* str, ...);
            void warn(const char* str, ...);
            void error(const char* str, ...);
            void fatal(const char* str, ...);

            template<typename T>
            inline void traceArray(const char* str, const T* array, int size) {
                logArray(TRACE, str, array, size);
            }

            template<typename T>
            inline void debugArray(const char* str, const T* array, int size) {
                logArray(DEBUG, str, array, size);
            }

            template<typename T>
            inline void infoArray(const char* str, const T* array, int size) {
                logArray(INFO, str, array, size);
            }

            template<typename T>
            inline void warnArray(const char* str, const T* array, int size) {
                logArray(WARN, str, array, size);
            }

            template<typename T>
            inline void errorArray(const char* str, const T* array, int size) {
                logArray(ERROR, str, array, size);
            }

            template<typename T>
            inline void fatalArray(const char* str, const T* array, int size) {
                logArray(FATAL, str, array, size);
            }

        private:
            void log(Level level, const char* str, va_list args);

            template<typename T>
            void logArray(Level level, const char* str, const T* array, int size) {
                if (level < LOG_LEVEL) {
                    return;
                }

                char buf[strlen(m_Prefix) + (m_Tag == nullptr ? 0 : strlen(m_Tag)) + 2];
                strcpy(buf, m_Prefix);
                if (m_Tag != nullptr) {
                    strcat(buf, ":");
                    strcat(buf, m_Tag);
                }

                Serial.printf("[%-5s] [%s] %s", levelToString(level), buf, str);

                for (size_t i = 0; i < size; i++) {
                    Serial.print(array[i]);
                }

                Serial.println();
            }

            const char* const m_Prefix;
            char* m_Tag;
        };
    } // namespace Logging
} // namespace SlimeVR

#endif
