#include"sql_select.h"

sql_select::sql_select(vector<string> ptr):value(ptr)
{
    
}
sql_select::~sql_select()
{

}
string sql_select::select()
{
    printf("mysql_begin\n");

    //cout<<"value1:"<<value1<<endl;

    MYSQL* connfd=mysql_init(NULL);   
    if (!connfd)         //判断是否初始化成功
    {
        printf("mysql初始化失败!\n");
       
    }                                         //初始化
    if(!mysql_real_connect(connfd,"localhost","root",NULL,NULL,0,NULL,0))  //连接
        {
            printf("sorry\n");
            printf("mysql_real_connect(): %s\n", mysql_error(connfd)); 
        }
    mysql_query(connfd,"use mytest"); 
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind[2];
    MYSQL_RES     *prepare_meta_result;
    char          passwd[STRING_SIZE];
    const char          *id;
    
    //strncpy(id,value1.c_str(),value1.length());
    id=value[0].c_str();
    //printf("size:%d\n",sizeof(id));
    //printf("length:%d\n",strlen(id));
    //printf("id:%s\n",id);
    char          path[STRING_SIZE];
    unsigned long length[2];
    int           param_count, column_count, row_count;
    bool       is_null[2];

    /* Prepare a SELECT query to fetch data from test_table */
    stmt = mysql_stmt_init(connfd);
    mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE));
    prepare_meta_result = mysql_stmt_result_metadata(stmt);

        MYSQL_BIND params[1];
        memset(params, 0, sizeof(params));
        params[0].buffer_type = MYSQL_TYPE_STRING;
        params[0].buffer = (char *)id;
        params[0].buffer_length=strlen(id); //importent;
        params[0].length=0;  //输入参数的长度设为0；
        params[0].is_null=0;

        mysql_stmt_bind_param(stmt,params);


    /* Execute the SELECT query */
    mysql_stmt_execute(stmt);

    /* Bind the result buffers for all 4 columns before fetching them */
    memset(bind, 0, sizeof(bind));
    /* INTEGER COLUMN */
    bind[0].buffer_type= MYSQL_TYPE_STRING;
    bind[0].buffer= (char *)passwd;
    bind[0].buffer_length=STRING_SIZE;
    bind[0].is_null= &is_null[0];
    bind[0].length= &length[0];

    /* STRING COLUMN */
    bind[1].buffer_type= MYSQL_TYPE_STRING;
    bind[1].buffer= (char *)path;
    bind[1].buffer_length= STRING_SIZE;
    bind[1].is_null= &is_null[1];
    bind[1].length= &length[1];

    /* Bind the result buffers */
    mysql_stmt_bind_result(stmt, bind);
    /* Now buffer all results to client */
    mysql_stmt_store_result(stmt);

    while (!mysql_stmt_fetch(stmt))
    {
    printf("passwd:%s\n",passwd);
    printf("path:%s\n",path);
    }

    printf("go\n");
    printf("123\n");
    //
    const  char* pswd;
    pswd=value[1].c_str();
    if(strcmp(pswd,passwd)==0)   //value2=passwd
    {   
            //cout<<"ok\n";
        	string ptr(&path[0],&path[strlen(path)]);
        return ptr;
    }
    mysql_free_result(prepare_meta_result);
    mysql_stmt_close(stmt);
    return string();
}