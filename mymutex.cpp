#include"mymutex.h"
mymutex::mymutex()
{
    if(pthread_mutex_init(&t_mutex,nullptr)!=0)
    std::cout<<"mutex_init_error";
}
mymutex::~mymutex()
{
    pthread_mutex_destroy(&t_mutex);
}
bool mymutex::lock()
{
    return pthread_mutex_lock(&t_mutex)==0;
}
bool mymutex::unlock()
{
  return pthread_mutex_unlock(&t_mutex)==0;
}