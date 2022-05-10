#ifndef YEWU_H
#define YEWU_H
#include"http_router.h"

    void test1(http_context context){
        cout<<"这是test1,我的url是"<<context.Url()<<"  我的方法是:"<<context.Method()<<endl;
    }
    void test2(http_context context){
        cout<<"这是test2,我的url是"<<context.Url()<<"  我的方法是:"<<context.Method()<<endl;
    }
     void test3(http_context context){
        cout<<"这是test3,我的url是"<<context.Url()<<"  我的方法是:"<<context.Method()<<endl;
        context.ResponseWriter("When do we go back?");
    }

    void thistest(){
        Router::RegisterGet("/1",test3);
        Router::RegisterGet("/2",test3);
        Router::RegisterGet("/3",test3);
        Router::RegisterGet("/4",test3);
        Router::RegisterGet("/5",test3);
        Router::RegisterGet("/6",test3);
        Router::RegisterGet("/7",test3);
        Router::RegisterGet("/8",test3);
        Router::RegisterGet("/9",test3);
        Router::RegisterGet("/10",test3);
        Router::RegisterGet("/11",test3);
        Router::RegisterGet("/12",test3);
        Router::RegisterGet("/13",test3);
        Router::RegisterGet("/14",test3);
        Router::RegisterGet("/15",test3);
        Router::RegisterGet("/16",test3);
        Router::RegisterGet("/17",test3);
        Router::RegisterGet("/18",test3);
        Router::RegisterGet("/19",test3);
        Router::RegisterGet("/20",test3);
        Router::RegisterGet("/21",test3);
        Router::RegisterGet("/22",test3);
        Router::RegisterGet("/23",test3);
        Router::RegisterGet("/24",test3);
        Router::RegisterGet("/25",test3);
        Router::RegisterGet("/26",test3);
        Router::RegisterGet("/27",test3);
        Router::RegisterGet("/28",test3);
        Router::RegisterGet("/29",test3);
        Router::RegisterGet("/30",test3);
        
    }

#endif