#include<semaphore.h>
#include<iostream>
class mysem
{
    private:
    sem_t t_sem;

    public:
    //init
    mysem();
    //destory
    ~mysem();
    //post
    bool post();
    //wait
    bool wait();
};

