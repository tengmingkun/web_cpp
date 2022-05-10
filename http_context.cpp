#include"http_context.h"

    void http_context::assemble_context(int sock,string rbody,string rmethod,string rurl,string rhttp_v,
        unordered_map<string,string> rhead,unordered_map<string,string> rkey_value){
            socket=sock;
            body=rbody;
            method=rmethod;
            url=rurl;
            http_v=rhttp_v;
            head=rhead;
            key_value=rkey_value;
    }
    //查询参数；
    string http_context::Query(string key){
        if(key_value.count(key)==0)
            return "";
        else {
            return key_value[key];
        }
    }
    //获取Body
    string http_context::Body(){
        return body;
    }
    //获取http版本
    string http_context::Http_v(){
        return http_v;
    }
    //获取Url
    string http_context::Url(){
        return url;
    }
    //获取method
    string http_context::Method(){
        return method;
    }
    //回复http请求
    void http_context::ResponseWriter(string str){
       
        //写头部；
       char buf[4096];
        //写头部；
        strcpy(buf,"HTTP/1.0 200 OK\r\n");
        send(socket,buf,strlen(buf),0);

        //服务器信息；
        strcpy(buf,"Server: This is tengmk Host\r\n");
        send(socket,buf,strlen(buf),0);

        strcpy(buf,"Content-Type: application/json\r\n");
        send(socket,buf,strlen(buf),0);

        strcpy(buf,"Connection: keep-alive\r\n");
        send(socket,buf,strlen(buf),0);

        strcpy(buf, "\r\n");
        send(socket, buf, strlen(buf), 0);
        
        char *buff=new char [str.size()+2];
        for(int i=0;i<str.size();i++)
            buff[i]=str[i];
        buff[str.size()]='\r';
        buff[str.size()+1]='\n';
        send(socket,buff,strlen(buff),0);
        delete buff;
        close(this->socket);
    }
     void http_context::ResponseGetHaveBody(){
          //写头部；
        char buf[1024];
        //写头部；
        strcpy(buf,"HTTP/1.0 200 OK\r\n");
        send(socket,buf,strlen(buf),0);
        cout<<"回复错误信息"<<endl;
        //服务器信息；
        strcpy(buf,"Server: This is tengmk Host\r\n");
        send(socket,buf,strlen(buf),0);

        strcpy(buf,"Content-Type: application/json\r\n");
        send(socket,buf,strlen(buf),0);
        // strcpy(buf,"Connection: keep-alive\r\n");
        // send(socket,buf,strlen(buf),0);
        strcpy(buf, "\r\n");
        send(socket, buf, strlen(buf), 0);
        close(this->socket);
     }