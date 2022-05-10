#include"epool.h"
    m_epool::m_epool(int socket)
    {
        serve_sock=socket;
        epollfd=epoll_create(1024);
        //设置监听描述符
        struct epoll_event ev;
        ev.events=EPOLLIN;
        ev.data.fd=serve_sock;
        epoll_ctl(epollfd,EPOLL_CTL_ADD,serve_sock,&ev);
        //std::cout<<"m_epoll:"<<serve_sock<<std::endl;
    }
    
    m_epool::~m_epool()
    {
        delete thread_pool;
    }
    void m_epool::unit()
    {   
       // std::cout<<"epool_unit"<<std::endl;
        thread_pool=new threadpool<do_request>(3000,1024);
        thread_pool->start();

        //开启定时器；
        mytimer.start();
    }
    void m_epool::run()
    {   
        //std::cout<<"run"<<std::endl;
        while(1)
        {   //std::cout<<"while"<<std::endl;
            int nready=epoll_wait(epollfd,events,1024,0);
            //std::cout<<"nready:"<<std::endl;
        for(int i=0;i<nready;i++)
        {
            if(events[i].data.fd==serve_sock) 
            {   
                int client_sock=accept(serve_sock,nullptr,nullptr);
                struct epoll_event tmp;
                tmp.data.fd=client_sock;
                tmp.events=EPOLLIN;
                epoll_ctl(epollfd,EPOLL_CTL_ADD,client_sock,&tmp);
            }
            else if(events[i].events&(EPOLLIN))
            {   
                //pthread_create(&newthread,NULL,accept_request,events[i].data.fd);
                //创建任务；//任务完成后，由线程进行释放；
                do_request * request=new do_request(events[i].data.fd);
                cout<<"fd是:"<<events[i].data.fd<<endl;
                //将任务加入线程池；
                thread_pool->task_append(request);
                //remenber to DEL it
                //释放epoll标记
                //这是短链接；
                //将时间加入定时器，达到时进行取消；
                struct timeval nowtime;
                gettimeofday(&nowtime,NULL);
                nowtime.tv_sec+=10;
                Timer t_time;
                t_time.epollfd=epollfd;
                t_time.serve_sock=events[i].data.fd;
                t_time.time=nowtime;
                mytimer.addtask(t_time);
            }
        }
        }
    }