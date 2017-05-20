//
// Created by Sourav on 5/13/2017.
//

#ifndef LOGGER_WORKITEM_H
#define LOGGER_WORKITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "thread.h"
#include "WorkerQueue.h"

class WorkItem
{
    std::string m_message;
    int    m_number;

public:
    WorkItem(const char* message, int number)
            : m_message(message), m_number(number) {}
    ~WorkItem() {}

    const char* getMessage() { return m_message.c_str(); }
    int getNumber() { return m_number; }
};
#endif //LOGGER_WORKITEM_H
