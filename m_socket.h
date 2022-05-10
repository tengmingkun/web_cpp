#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<string>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<poll.h>
#include<sys/epoll.h>
#include<mysql/mysql.h>
#include<malloc.h>
//#include"epool.h"
class m_socket{

    private:
    int server_sock;
    public:
    //创建监听描述符
    m_socket(ushort port);
    
    //关闭监听描述符
    ~m_socket();

    //返回监听描述符；
    int get_sock();

    

};
