/* 
    *Created by tengmk 2022-2-23
    此类为上下文信息类
*/

#ifndef _HTTP_CONTEXT_H
#define _HTTP_CONTEXT_H
#include<vector>
#include<iostream>
#include<unordered_map>
#include<string.h>
#include<sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
class http_context {
    public:
    http_context(){

    }
    ~http_context(){

    }

    //组装context；
    void assemble_context(int sock,string body,string method,string url,string http_v,
    unordered_map<string,string> head,unordered_map<string,string> key_value);
    //查询参数；
    string Query(string key);
    //获取Body
    string Body();
    //获取http版本
    string Http_v();
     //获取Url
    string Url();
    //获取Method
    string Method();
    //应答http请求；
    void ResponseWriter(string );
    // GET请求带Body
    void ResponseGetHaveBody();

    private:
    int socket;    //套接字
    string body;   //请求体
    string method; //方法
    string url;    //url
    string http_v; //http版本;
    unordered_map<string,string> head;// 请求头
    unordered_map<string,string> key_value;// 请求头
};

#endif