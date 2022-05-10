#include<vector>
#include<string>
#include<mysql/mysql.h>
#include <string.h>
#define SELECT_SAMPLE "SELECT passwd, path FROM student WHERE id=?"
#define STRING_SIZE 50
#define ISspace(x) isspace((int)(x))
using std::vector;
using std::string;

class sql_select
{
private:
    vector<string> value;
public:

    sql_select(vector<string> ptr);
    ~sql_select();

    //数据库查询函数
    string select();

};
