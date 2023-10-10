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
#ifndef _THREAD_H
#define _THREAD_H 1

#include <iostream>
#include <pthread.h>

class Thread {
public:
    void start(); 
    void stop();
    virtual void run() = 0;

protected:
    pthread_t tid;
};

void *task(void *arg);

#endif /* _THREAD_H */