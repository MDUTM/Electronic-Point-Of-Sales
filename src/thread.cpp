/**
 * @file    thread.h
 * @version 1.0
 * @brief   线程类
 * 
 * @author  MDUTM  MDUTM@outlook.com
 * @date    2023-09-26
 * 
 * @copyright Copyright (c) 2023 MDUTM
 */
#include "thread.h"

void Thread::start()
{
    pthread_create(&tid, nullptr, task, this);
    pthread_detach(tid);
}

void Thread::stop()
{
    pthread_cancel(tid);
}

void *task(void *arg)
{
    Thread *th = static_cast<Thread *>(arg);
    th->run();

    return nullptr;
}
