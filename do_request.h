#ifndef DO_REQUEST_H
#define DO_REQUEST_H
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <string.h>
#include<ctype.h>
#include<mysql/mysql.h>
#define SELECT_SAMPLE "SELECT passwd, path FROM student WHERE id=?"
#define STRING_SIZE 50
#define ISspace(x) isspace((int)(x))
#include<malloc.h>
#include<sys/socket.h>
#include <unistd.h>
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<vector>
#include<unordered_map>
#include"sql_select.h"
#include"http_router.h"
using namespace std;
class do_request{
    private:
    int cli_sock;
    string content;
    string method;
    string url;
    string http_v;
    vector<string > form;
    map<string,string> hearders;

    string Method;
    string Http_v;
    string Url;
    unordered_map<string,string> Key_Value;
    unordered_map<string,string> Head;
    string Body="";
    
    public:
    http_context context;


    public:
    //保存客户套字
    do_request(int socket);

    //关闭客户套接字
    ~do_request();

    //对外接口函数，方便线程池调用；
    void run();

    //数据解析；
    void data_prase(int client);
    //从tcp缓存读取一行
    int get_line(int sock,char* buf ,int size) ;
    int read_all(int sock,char* buf,int size);
    //解析头部；
    void prase_http_header(int client);
    void prase_http_head(int client);
    bool prase_http_body(int client);
    void prase_header();
    //解析参数
    void prase_value();
    //解析sql查询的参数
    vector<string>  sql_prase(string str1,string str2);
    //将tcp中内容读完；
    void serve_file(int client,const char *path);
    //写tcp头部
    void write_date(int client,FILE *resource);
    //写tcp数据
    void write_head(int client,const char *path);
    // 解析请求
    void prase_req(int client);
    //寻找路由，执行函数；
    void go_router();

};

#endif