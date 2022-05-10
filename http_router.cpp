#include"http_router.h"
    unordered_map<string,Fun>  Router::router_GET;
    unordered_map<string,Fun>  Router::router_POST;
    void Router::RegisterGet(string url,Fun fun){
            if(Router::router_GET.count(url)==0){
                Router::router_GET[url]=fun;
            } else {
                cout<<"此路由注册错误:"<<url<<endl;
                return ;
            }
        }
        void Router::RegisterPost(string url,Fun fun){
            if(Router::router_POST.count(url)==0){
                Router::router_POST[url]=fun;
            } else {
                cout<<"此路由注册错误:"<<url<<endl;
                return ;
            }
        }

