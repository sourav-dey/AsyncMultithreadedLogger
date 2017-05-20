#ifndef LOGGER_WORKERQUEUE_H
#define LOGGER_WORKERQUEUE_H

#include <pthread.h>
#include <queue>

template<typename T> class WorkerQueue {
    std::queue<T> m_queue;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
    static WorkerQueue *m_instance;

public:
    WorkerQueue() {
        pthread_mutex_init(&m_mutex, nullptr);
        pthread_cond_init(&m_cond, nullptr);
    }

    ~WorkerQueue() {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
    }

    inline std::queue<T> getQueue() {
        return m_queue;
    }

    void add(T item) {
        pthread_mutex_lock(&m_mutex);
        m_queue.push(item);
        pthread_cond_signal(&m_cond);
        pthread_mutex_unlock(&m_mutex);
    }

    T remove() {
        pthread_mutex_lock(&m_mutex);
        while (m_queue.empty()) {
            pthread_cond_wait(&m_cond, &m_mutex);
        }
        T item = m_queue.front();
        m_queue.pop();
        pthread_mutex_unlock(&m_mutex);
        return item;
    }

    size_t size() {
        pthread_mutex_lock(&m_mutex);
        size_t size = m_queue.size();
        pthread_mutex_unlock(&m_mutex);
        return size;
    }
};
#endif //LOGGER_WORKERQUEUE_H
