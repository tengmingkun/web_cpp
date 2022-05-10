#ifndef HTTP_TIMERS_H
#define HTTP_TIMERS_H
#include<unordered_map>
#include<queue>
#include"mymutex.h"
#include<vector>
#include<pthread.h>
#include<unistd.h>
#include <sys/time.h>
#include<sys/epoll.h>
#include<poll.h>
using namespace std;
class Timer{
    public:
    struct timeval time;//最后的到达时间
    int serve_sock;         //监听套接字
    int epollfd;            //epoll文件描述符
};
struct cmp{ //默认是大根堆，改成小根堆
     bool operator() ( Timer &a, Timer &b ){//默认是less函数
        //返回true时，a的优先级低于b的优先级（a排在b的后面）
        if((a.time.tv_usec+a.time.tv_sec)>(b.time.tv_usec+b.time.tv_sec)) 
            return true;
        return false;
    }
 };

class http_timers
{

    public:
    pthread_t threads;
    mymutex mutexs;
    priority_queue<Timer, vector<Timer>, cmp> node ;//用优先队列省去了 遍历的O（n）时间；
    unordered_map<int,struct timeval > latest;   //用一个哈希表，可以决定是否关闭套接字；
    public:
    http_timers(/* args */);
    ~http_timers(); 
    void start();
    //静态函数调用run
    //线程无限循环
    void run();
    void do_close(Timer time);
    void getnum(int a);
    static void* worker(void *arg);
    void addtask(Timer time);
};
#endif
