#include"do_request.h"
using namespace std;
    //构造函数
    do_request::do_request(int socket){
        cli_sock=socket;
    }
    //析构函数
    do_request::~do_request(){

    }
    //事件封装的接口；
    void do_request::run(){   
        //std::cout<<"do_re_run"<<std::endl;
        prase_req(cli_sock);
    }
    // 读取所有内容（revc和postman存在冲突）！！！
    int do_request::read_all(int sock,char *buf,int size){
        memset(buf, 0, size);
        int n=read(sock,buf,size);
        return n;
    }
    //读取一行
    int do_request::get_line(int sock,char* buf ,int size) {   
    // 必须清空！！！
        memset(buf, 0, size);
        int i=0;
        char c='\0';
        int n;
        while((i<size-1)&&(c!='\n'))//当数组不满，且不到'\r'或'\n'的时候。
        {
            n=recv(sock,&c,1,0);//读一个字节
            if(n>0)  //读到了
            {  
                if(c=='\r')  //防止'\r\n'的情况,
                {  // cout<<'b'<<endl;
                    n=recv(sock,&c,1,MSG_PEEK);//不清除；
                    //cout<<"n2"<<n<<endl;
                    if((n>0)&&(c=='\n'))  //如果再读的是'\n
                        {
                        //cout<<'c'<<endl;
                        recv(sock,&c,1,0); //清掉；
                        }
                    else                //否则停止读。
                        c='\n';
                }
                buf[i]=c;
                i++;
            }
            else 
                break;
        }
        buf[i]='\0';
        return i;
    }

    vector<string> do_request::sql_prase(string str1,string str2)
{
    int i;
    int j;
    string  id;
    string  passwd;
    //std::cout<<"str1:"<<str1<<std::endl;
    //std::cout<<str2<<std::endl;
    //printf("str2:%s\n",str2);
     i=0;
    while(str1[i]!='=')
    {   
        std::cout<<str1[i]<<std::endl;
        i++;
    }
    i++;
     //printf("I1:%d\n",i);
    
    j=0;
    while(1)
    {   
        if(str1[i]=='\0')
            break;
        id.push_back(str1[i]);
        i++;
    }
    //id[i]='\0';
   
    i=0;
    while(str2[i]!='=')
    i++;
    i++;
    printf("I2:%d\n",i);

    while(1)
    {   printf("str2:%c\n",str2[i]);
        if(str2[i]=='\0')
        break;
        else
        {
            passwd.push_back(str2[i]);
        i++;
        }
    }
    passwd[i]='\0';
    //string path=mysql_login(id,passwd);
    //mysql_login(id,passwd);
   return {id,passwd};
}
    //解析http第一行
    void do_request::prase_http_header(int client){
        //获得请求的第一行；
        char buf[1024];
        int numchars=get_line(client,buf,sizeof(buf));
        string header(buf,buf+numchars);
        //解析方法
        if(header.find("GET")!=header.npos)
            this->Method="GET";
        else if (header.find("POST")!=header.npos)
            this->Method="POST";
        
        //解析http版本；
        int pos=header.find_last_of("HTTP");
        pos=pos+2;
        this->Http_v=string(header.begin()+pos,header.end());

        //解析Url
        //如果有参数
        pos = header.find_first_of("?");
        string value_str; //保存参数的字符串
        if(pos != header.npos){
            if(this->Method=="POST"){
                //如果方法是POST
                Url = string(header.begin()+5,header.begin()+pos);
            }    
            else if(this->Method=="GET"){
                //如果方法是GET
                Url = string(header.begin()+4,header.begin()+pos);
            }
            //把参数字符串存起来
            int pos2=header.find_last_of(" ");
            value_str = string (header.begin()+pos+1,header.begin()+pos2);
            
        }
        else { //没有参数
            int pos1=header.find_first_of(" ");
            int pos2=header.find_last_of(" ");
            Url = string(header.begin()+pos1+1,header.begin()+pos2);
            return ;
        }

        //解析参数
        vector<string> v_value;
        //用 & 将字符串分隔开；
        while(value_str.find("&") != value_str.npos){
            pos=value_str.find("&");
            v_value.push_back(string(value_str.begin(),value_str.begin()+pos));
            value_str=value_str.substr(pos+1);
        }
        v_value.push_back(value_str);
        // 用map数组存储起来
         for(auto str:v_value){
             pos=str.find("=");
             string key=string(str.begin(),str.begin()+pos);
             string value=string(str.begin()+pos+1,str.end());
            Key_Value[key]=value;
         }

    }
    void do_request::prase_header()
    {   
        int n;
        if(content.find("GET")!=content.npos)
            {
                method="GET";
                content=content.substr(4);
            }
        else if(content.find("POST")!=content.npos)
            {
                method="POST";
                content=content.substr(5);
            }
            cout<<method<<endl;
            //cout<<"content2:"<<content<<endl;
        for(int i=0;i<content.size();i++)
        {
            if(content[i]!=' ')
                url.push_back(content[i]);
            else break;
        }
        cout<<"url:"<<url<<endl;
        content=content.substr(url.size()+1+5);
        

         //cout<<"content3:"<<content<<endl;
        http_v=content;
        cout<<http_v<<endl;
        //content.clear();
        content=url;
        n=url.find('?');
        url=url.substr(0,n);

        cout<<"url:"<<url<<endl;
        if((n=content.find('?'))==content.npos)
            return;
        else 
            content=content.substr(n);
        
        //int i=0;
        string value;
        n=content.find('=');
        content=content.substr(n+1);
        for(int i=0;i<content.size();i++)
        {
            if(content[i]!='&')
                value.push_back(content[i]);
            else break;
        }
        //cout<<"value1:"<<value1<<endl;
        form.push_back(value);
        value.clear();
        n=content.find('=');
        content=content.substr(n+1);
        for(int i=0;i<content.size();i++)
        {
            if(content[i]!='&')
                value.push_back(content[i]);
            else break;
        }
        form.push_back(value);
        //cout<<"value2:"<<value2<<endl
        //cout<<"form"<<form["tmk"]<<endl;
    }

    void do_request::prase_value()
    {
        int pos;
        string value1;
        pos=content.find(":");
        value1=content.substr(0,pos-1);
        content=content.substr(pos+2);
        string value2=content;
        hearders[value1]=value2;

    }
    //请求解析
    void do_request::prase_req(int client){
        this->prase_http_header(client);
        this->prase_http_head(client);
        if(Method=="POST")
            this->prase_http_body(client);
        // 写上下文信息；
        context.assemble_context(cli_sock,Body,Method,Url,Http_v,Head,Key_Value);
        //执行路由
        this->go_router();
    }
   
    //寻找路由，执行函数
    void do_request::go_router(){
        string method=context.Method();
        string url=context.Url();
        if(method=="GET"){
            if(Router::router_GET.count(url)==1)
                Router::router_GET[url](context);
            else 
                close(this->cli_sock);
        }
        if(method=="POST"){
            if(Router::router_POST.count(url)==1)
                Router::router_POST[url](context);
            else 
                close(this->cli_sock);
        }
    }
    //解析头部
    void do_request::prase_http_head(int client){
        while(1){
            char buf[1024];
            int numchars=get_line(client,buf,sizeof(buf));
            //读到了数据且不是空行
            if((numchars>0)&&strcmp("\n",buf)){
                string head(buf,buf+numchars);
                int pos=head.find(":");
                string key=string(head.begin(),head.begin()+pos);
                string value=string(head.begin()+pos+1,head.end());
                Head[key]=value;
            }else 
                return;
        }
    }
    //解析body
    bool do_request::prase_http_body(int client){
        char buf[1024];
        int numchars=read_all(client,buf,sizeof(buf));
        string body(buf,buf+numchars);
        Body=Body+body;
        return true;
    }
    //解析请求；
    void do_request::data_prase(int client)
{
    std::cout<<"accept_request"<<std::endl;
    char buf[1024];
    int numchars;
    char path[1024];
    size_t i,j;
    struct stat st;
    int cgi=0;
    char *query_string=NULL;

    //获得请求的第一行；
    numchars=get_line(client,buf,sizeof(buf));
    string tmp(buf,buf+numchars);
    content+=tmp;
    this->prase_header();
    cout<<numchars<<endl;
    
    //解析参数,读每一行，进行解析
    hearders.clear();
    while((numchars>0)&&strcmp("\n",buf))
    {
        numchars=get_line(client,buf,sizeof(buf));
       string tmp(buf,buf+numchars);
        content.clear();
        content+=tmp;
       this->prase_value();
    }
    cout<<"headersize"<<hearders.size()<<endl;

    
    if(method!="GET")//不是get方法；
    {   
        printf("ispost");
        return;
    }
    

    if(url=="/LOGIN")  //是登录页面发来的东西
    {   
        //定义数据库对象
        sql_select sqlselect(form);
        //数据库查询函数
        string ptr=sqlselect.select();

     
        strncpy(path,ptr.c_str(),ptr.length());
     
    }
    else if(url=="/") //将路径设为htdocs/index.html
       strcat(path,"htdocs/login_in.html");
    else 
    {
        url=url.substr(1);
        strncpy(path,url.c_str(),url.length());
    }

     
    printf("path:%s\n",path);
    if(stat(path,&st)==-1)//找不到文件,将头部全部都掉。
    {   
        printf("notfound\n");
        //while((numchars>0)&&strcmp("\n",buf))
        //    numchars=get_line(client,buf,sizeof(buf));
    }
    else{  //找到了
        if((st.st_mode&S_IFMT)==S_IFDIR)//如果是目录
            strcat(path,"/index.html");
            
            serve_file(client,path);  //服务.
    }
    
}
    void do_request::serve_file(int client,const char *path)
{   
    FILE * resource=NULL;
    int numchar=1;
    char buf[1024];
    //while((numchar>0)&&strcmp("\n",buf))  //将头部全部读出来
     //   numchar=get_line(client,buf,sizeof(buf));
    resource=fopen(path,"r");
    if(resource==NULL)
        return;
    else
    {
        write_head(client,path);  //写头部；
        write_date(client,resource); //复制文件；
        close(cli_sock);
        delete this;
    }
    fclose(resource);
    
}

    void do_request::write_date(int client,FILE *resource)
{
    char buf[1024];
    fgets(buf,sizeof(buf),resource);
    while(!feof(resource))  //检测流上的文件结束符。
    {
        send(client,buf,strlen(buf),0);
        fgets(buf,sizeof(buf),resource);
    }
}

    void do_request::write_head(int client,const char *path)
{
    char buf[1024];
    (void)path;
    //写头部；
    strcpy(buf,"HTTP/1.0 200 OK\r\n");
    send(client,buf,strlen(buf),0);

    //服务器信息；
    strcpy(buf,"Server: t/0.1.0\r\n");
    send(client,buf,strlen(buf),0);

    strcpy(buf,"Content-Type: text/html\r\n");
    send(client,buf,strlen(buf),0);
    strcpy(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    close(client);
}
