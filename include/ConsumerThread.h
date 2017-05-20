#ifndef LOGGER_CONSUMERTHREAD_H
#define LOGGER_CONSUMERTHREAD_H

#include <atomic>
#include "Thread.h"
#include "WorkerQueue.h"
#include "Logger.h"
#include "WorkItem.h"

class ConsumerThread : public Thread {
    WorkerQueue<Logger::LogStruct *>& m_queue;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
    std::atomic<bool> m_done;

public:
    ConsumerThread(WorkerQueue<Logger::LogStruct *> &queue)
            : m_queue(queue)
            , m_done(false)
    {}

    void *run() {
        pthread_mutex_lock(&m_mutex);
        while(Logger::instance()->m_queue.size() == 0) {
            pthread_cond_wait(&m_cond, &m_mutex);
        }

        if (Logger::instance()->m_queue.size() != 0 ) {
            m_done = false;
        }

        while(!m_done) {
            Logger::LogStruct *item = (Logger::LogStruct*)Logger::instance()->m_queue.remove();
            Logger::instance()->writetoFile(item->logtype, item->message);
            delete item;

            if (Logger::instance()->m_queue.size() == 0) {
                m_done = true;
            }
        }
        return NULL;
    }
};
#endif //LOGGER_CONSUMERTHREAD_H
