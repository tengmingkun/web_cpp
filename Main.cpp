//#include"do_request.h"
#include"epool.h"
#include"yewu.h"
//#include"threadpool.h"

//编译命令
//g++ -o test Main.cpp yewu.cpp  threadpool.h epool.cpp http_timers.cpp m_socket.cpp  do_request.cpp http_router.cpp  http_context.cpp  sql_select.cpp  mysem.cpp mymutex.cpp -lpthread  `mysql_config --cflags --libs` 
#include"m_socket.h"
int main()
{
    m_socket  my_serve(0);  //创建服务端套接字；
    m_epool     my_epool(my_serve.get_sock());  //epoll循环；
    my_epool.unit();//开启线程池；
    thistest();//注册路由
    my_epool.run();//启动循环


}