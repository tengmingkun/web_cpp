#include"m_socket.h"
m_socket::m_socket(ushort port)
{
    struct sockaddr_in serveaddr;
    int listened;
    listened=socket(AF_INET,SOCK_STREAM,0);
    bzero(&serveaddr,sizeof(serveaddr));
    serveaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveaddr.sin_port=htons(port);
    serveaddr.sin_family=AF_INET;
    bind(listened,(struct sockaddr*)&serveaddr,sizeof(serveaddr));
    listen(listened,1024);
    //setsockopt(listened,SOL_SOCKET,SO_REUSEADDR,1,NULL);
     if (port == 0)  /* if dynamically allocating a port */
    {
        unsigned int namelen = sizeof(serveaddr);
        if (getsockname(listened, (struct sockaddr *)&serveaddr, &namelen) == -1)
            return ;
        port = ntohs(serveaddr.sin_port);
    }
    server_sock=listened;
    std::cout<<"http://120.76.99.69:"<<port<<std::endl;
}
    m_socket::~m_socket()
    {
        close(server_sock);
    }

int m_socket::get_sock()
    {
        return server_sock;
    }
