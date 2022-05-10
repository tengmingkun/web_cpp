#ifndef EPOLL_H
#define EPOLL_H
#include<sys/epoll.h>
#include<poll.h>
#include<sys/socket.h>
#include"threadpool.h"
#include"do_request.h"
#include<new>
#include"http_timers.h"
class m_epool{
    private:
    int serve_sock;         //监听套接字
    int epollfd;            //epoll文件描述符
    struct epoll_event events[1024];//epoll事件
    threadpool<do_request> *thread_pool;  //指向线程池的指针；
    http_timers mytimer;
    public:
    //using threadpool<do_request>::start();
    
    //创建epoll轮询
    m_epool(int socket);
    
    //释放线程池
    ~m_epool();
    
    //创建线程池，并开启线程池；
    void unit();
   
   //开启epoll循环；
    void run();

    //关闭连接，取消注册符号；



};
#endif