#include "include/Thread.h"

static void *runThread(void *arg);

Thread::Thread()
    :   m_tid(0),
        m_running(false),
        m_detached(false) {
}

Thread::~Thread() {
    if (m_running && !m_detached) {
        pthread_detach(m_tid);
    }

    if (m_running) {
        pthread_cancel(m_tid);
    }
}

int Thread::start() {
    int result = pthread_create(&m_tid, nullptr, runThread, this);
    if (result == 0) {
        m_running = true;
    }
    return result;
}

static void *runThread(void *arg) {
    return (static_cast<Thread *> (arg))->run();
}

int Thread::join() {
    int result = -1;
    if (m_running) {
        result = pthread_join(m_tid, nullptr);
        if (result == 0) {
            m_detached = true;
        }
    }
    return result;
}

int Thread::detach() {
    int result = -1;
    if (m_running && !m_detached) {
        result = pthread_detach(m_tid);
        if (result == 0) {
            m_detached = true;
        }
    }
    return result;
}

pthread_t Thread::self() {
    return m_tid;
}