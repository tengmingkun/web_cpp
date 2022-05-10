#include"http_timers.h"
void http_timers::addtask(Timer time){
    mutexs.lock();
    if(latest.count(time.serve_sock)>0){ //存在；
        latest[time.serve_sock]=time.time;
    } else {
        node.push(time);
        latest[time.serve_sock]=time.time;
    }
    mutexs.unlock();
}

http_timers::http_timers(/* args */)
{
}

http_timers::~http_timers()
{
}

void http_timers::getnum(int a){
    cout<<a<<endl;
}

void http_timers::start()  //启动线程池
{   
    pthread_create(&threads,nullptr,worker,this);
    pthread_detach(threads);

}
void http_timers::run(){
    cout<<"线程池工作"<<endl;
    while(1){
        while(!node.empty()){
            mutexs.lock();
            struct timeval now;
            gettimeofday(&now,NULL);
            auto mins=node.top();
            if(mins.time.tv_sec<now.tv_sec){
                if(latest[mins.serve_sock].tv_sec==mins.time.tv_sec&&
                    latest[mins.serve_sock].tv_usec==mins.time.tv_usec){
                        do_close(mins);
                        node.pop();
                        latest.erase(mins.serve_sock);
                        cout<<"nowshi:"<<now.tv_sec<<' '<<now.tv_usec<<endl;
                } else{
                        node.pop();
                        mins.time=latest[mins.serve_sock];
                        node.push(mins);
                }
            } else if(mins.time.tv_sec==now.tv_sec) {
                if(mins.time.tv_usec<now.tv_usec){
                    if(latest[mins.serve_sock].tv_sec==mins.time.tv_sec&&
                        latest[mins.serve_sock].tv_usec==mins.time.tv_usec){
                            do_close(mins);
                            node.pop();
                            latest.erase(mins.serve_sock);
                        } else {
                            node.pop();
                            mins.time=latest[mins.serve_sock];
                            node.push(mins);
                        }
                }
            }
            mutexs.unlock();
        }
    }

}
void* http_timers::worker(void *arg)
{
    http_timers *pool=(http_timers*) arg;
    pool->run();
    return pool;
}
 void http_timers::do_close(Timer time){
        close(time.serve_sock);
        cout<<"取消链接"<<time.serve_sock<<endl;
        epoll_ctl(time.epollfd,EPOLL_CTL_DEL,time.serve_sock,NULL);  
    }