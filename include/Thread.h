#ifndef LOGGER_THREAD_H
#define LOGGER_THREAD_H

#include <pthread.h>

class Thread {
private:
    pthread_t m_tid;
    bool m_running;
    bool m_detached;

public:
    Thread();
    virtual ~Thread();

    int start();
    int join();
    int detach();
    pthread_t self();

    virtual void *run() = 0;
};
#endif //LOGGER_THREAD_H
