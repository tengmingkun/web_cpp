#ifndef MYMUTEX_H
#define MYMUTEX_H
#include<pthread.h>
#include<iostream>
class mymutex
{
    private:
    pthread_mutex_t t_mutex;
    public:

    //init
    mymutex();
    //destory
    ~mymutex();
    //lock
    bool lock();
    //unlock
    bool unlock();
    
};

#endif