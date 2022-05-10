#ifndef THREADPOOL
#define THREADPOOL
#include"mysem.h"
#include"mymutex.h"
#include<list>
using namespace std;
template<class T>
class threadpool
{
    private:
    int thread_num;
    int max_task;
    pthread_t *threads;
    std::list<T*> worklist;
    mysem queue_sem;
    mymutex queue_mutex;
    bool stop;

    public:
    //构造函数
    threadpool(int t_thread_num=4,int t_max_task=1024);
    //析沟函数
    ~threadpool();
    //添加任务
    bool task_append(T* task);
    //启动线程池，创建线程；
    void start();
    private:
    //静态函数调用run
    static void* worker(void *arg);
    //线程无限循环
    void run();
};
template<class T>
threadpool<T>::threadpool(int t_thread_num,int t_max_task):thread_num(t_thread_num),max_task(t_max_task),
stop(false),threads(nullptr)
{   
    threads=new pthread_t[thread_num];
    
}

template<class T>
void threadpool<T>::start()  //启动线程池
{   
    for(int i=0;i<thread_num;i++)
    {   //std::cout<<"thread_start"<<std::endl;
        pthread_create(threads+i,nullptr,worker,this);
        pthread_detach(threads[i]);
    }
}
template<class T>
threadpool<T>::~threadpool()
{
    stop=true;
    delete []threads;
}
template<class T>
bool threadpool<T>::task_append(T* task)
{   
    queue_mutex.lock();
    if(worklist.size()>max_task)
        {
            std::cout<<"append_error";
            queue_mutex.unlock();
            return false;
        }
    worklist.push_back(task);  //添加；
    queue_sem.post();
    queue_mutex.unlock();
    return true;
}

template<class T>
void* threadpool<T>::worker(void *arg)
{
    threadpool *pool=(threadpool*) arg;
    pool->run();
    return pool;
}

template<class T>
void threadpool<T>::run()
{
    while(!stop)
    {   
        queue_sem.wait();
        queue_mutex.lock();
        if(worklist.size()==0)
            {
                queue_mutex.unlock();
                continue;
            }
        T* task=worklist.front();
        worklist.pop_front();
        queue_mutex.unlock();
        if(task==nullptr)
            continue;
        task->run();

    }

}
#endif