#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <string>
#include <thread>
#include <queue>
#include <stdio.h>
#include <stdarg.h>
#include "WorkerQueue.h"

#define LOGGER_MAXSIZE 1024

enum LogType {
    LOGGER_DEBUG = 0,
    LOGGER_INFO = 1,
    LOGGER_WARN = 1 << 1,
    LOGGER_ERROR = 1 << 2
};

class Logger {
private:
    static Logger *m_instance;
    LogType m_logginglevel;
    std::string m_fileName;
    bool m_flushEnabled;

public:
    struct LogStruct {
        LogType logtype;
        std::string message;

        LogStruct(LogType logType, std::string message) {
            this->logtype = logType;
            this->message = message;
        }
    };
    WorkerQueue<LogStruct *> m_queue;

    Logger() {
        m_flushEnabled = true;
        m_logginglevel = LOGGER_DEBUG;
        m_fileName = "Log.log";
    }

    ~Logger() {
        delete(m_instance);
        m_instance = nullptr;
    }

    static Logger *instance() {
        if (m_instance == nullptr) {
            m_instance = new Logger();
        }
        return m_instance;
    }

    inline void setLogginglevel(LogType logType) {
        m_logginglevel = logType;
    }

    inline void setLogFileName(std::string fileName) {
        m_fileName = fileName;
    }

    inline WorkerQueue<LogStruct *> getQueue() {
        return m_queue;
    }

    void debugInfo(LogType logType, std::string message);
    void log(LogType logType, char *message, ...);
    void writetoFile(LogType logType, std::string message);
};
#endif //LOGGER_LOGGER_H
