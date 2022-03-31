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

#include "Logger.h"

namespace SlimeVR {
    namespace Logging {
        void Logger::setTag(const char* tag) {
            m_Tag = (char*)malloc(strlen(tag) + 1);
            strcpy(m_Tag, tag);
        }

        void Logger::trace(const char* format, ...) {
            va_list args;
            va_start(args, format);
            log(TRACE, format, args);
            va_end(args);
        }

        void Logger::debug(const char* format, ...) {
            va_list args;
            va_start(args, format);
            log(DEBUG, format, args);
            va_end(args);
        }

        void Logger::info(const char* format, ...) {
            va_list args;
            va_start(args, format);
            log(INFO, format, args);
            va_end(args);
        }

        void Logger::warn(const char* format, ...) {
            va_list args;
            va_start(args, format);
            log(WARN, format, args);
            va_end(args);
        }

        void Logger::error(const char* format, ...) {
            va_list args;
            va_start(args, format);
            log(ERROR, format, args);
            va_end(args);
        }

        void Logger::fatal(const char* format, ...) {
            va_list args;
            va_start(args, format);
            log(FATAL, format, args);
            va_end(args);
        }

        void Logger::log(Level level, const char* format, va_list args) {
            if (level < LOG_LEVEL) {
                return;
            }

            char buffer[256];
            vsnprintf(buffer, 256, format, args);

            char buf[strlen(m_Prefix) + (m_Tag == nullptr ? 0 : strlen(m_Tag)) + 2];
            strcpy(buf, m_Prefix);
            if (m_Tag != nullptr) {
                strcat(buf, ":");
                strcat(buf, m_Tag);
            }

            Serial.printf("[%-5s] [%s] %s\n", levelToString(level), buf, buffer);
        }
    } // namespace Logging
} // namespace SlimeVR
