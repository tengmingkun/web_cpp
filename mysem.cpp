#include"mysem.h"
mysem::mysem()
{
    if(sem_init(&t_sem,0,0)!=0)
    {
        std::cout<<"sem_init_error";
    }
}
mysem::~mysem()
{
    if(sem_destroy(&t_sem)!=0)
    {
        std::cout<<"sem_destory_error";
    }

}
bool mysem::post()
{
    return sem_post(&t_sem)==0;
}
bool mysem::wait()
{
    return sem_wait(&t_sem)==0;
}