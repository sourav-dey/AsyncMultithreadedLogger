#include <cstring>
#include <iostream>
#include "include/Logger.h"

Logger *Logger::m_instance = nullptr;

void Logger::log(LogType logType, char *message, ...) {
    char finalMessage[LOGGER_MAXSIZE];

    va_list args;
    va_start(args, message);
    size_t size = (size_t) vsnprintf(nullptr, 0, message, args);
    va_end(args);

    va_start(args, message);
    vsnprintf(finalMessage, size + 1, message, args);
    va_end(args);
    debugInfo(logType, message);
}

void Logger::debugInfo(LogType logType, std::string message) {
    LogStruct *logStruct = new LogStruct(logType, message);
    m_queue.add(logStruct);
}

void Logger::writetoFile(LogType logType, std::string message) {
    printf("%s\n ", message.c_str());
    if (logType >= m_logginglevel) {
        FILE *fp = std::fopen(m_fileName.c_str(), "a+");
        if (!fp) {
            std::cerr << "File opening failed";
            return;
        } else {
            fprintf(fp, "%s\r\n", message.c_str());
        }

        if (m_flushEnabled) {
            fflush(fp);
        } else {
            fclose(fp);
            //fp = nullptr;
        }
    }
}
