/* 
    *Created by tengmk 2022-2-23
    此类为上下文信息类
*/

#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H
#include<vector>
#include<iostream>
#include<unordered_map>
#include"http_context.h"
#include<string>
using namespace std;
using Fun=void(*)(http_context);
class Router {
    public:
    Router(){
    }
    ~Router(){
    }
    static unordered_map<string,void(*)(http_context) > router_GET;
    static unordered_map<string,Fun> router_POST;
    static void RegisterGet(string url,Fun fun);
    static void RegisterPost(string url,Fun fun);
};  
   
#endif