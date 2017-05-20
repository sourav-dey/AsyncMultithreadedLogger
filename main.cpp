#include <iostream>
#include <unistd.h>
#include "include/Logger.h"
#include "include/ConsumerThread.h"

using namespace std;

int main() {
    WorkerQueue<Logger::LogStruct*>  queue = Logger::instance()->getQueue();
    ConsumerThread* thread1 = new ConsumerThread(queue);
    thread1->start();

    Logger::instance()->setLogginglevel(LOGGER_DEBUG);
    // Add items to the queue
    Logger* item;
    for (int i = 0; i < 3; i++) {
        Logger::instance()->log(LOGGER_DEBUG, (char *) "Hi");
        Logger::instance()->log(LOGGER_DEBUG, (char *) "Bye");
    }
    sleep(2);
    exit(0);
}