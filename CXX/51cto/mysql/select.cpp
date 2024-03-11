#include <iostream>
#include <mysql.h>

int main(int argc, char *argv[]) {

    MYSQL mysql;
    mysql_init(&mysql);

    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *passwd = "密码";
    const char *db = "mysql";  // tqzschema

    // 连接登录数据库
    bool connect_ret = mysql_real_connect(&mysql, host, user, passwd, db, 3306, 0, 0);
    if (!connect_ret) { // 登录失败
        std::cout << "connect failed: " << mysql_error(&mysql) << std::endl;
    } else {
        std::cout << "connect success: " << host << std::endl;
    }
    
    
    // user select * from user;
    //1. 执行sql语句;
    const char *sql = "select * from user";
    // mysql_real_query sql语句中可以包含二进制数据
    // mysql_query sql语句中只能是字符串
    
    int ret = mysql_real_query(&mysql, sql, strlen(sql));
    if (ret != 0) {
        std::cout << "mysql_real_query faied!: " << sql << mysql_error(&mysql) << std::endl;
    } else {
        std::cout << "mysql_real_query success!: " << sql << std::endl;
    }
    
    
    // 2. 获取结果集
    // MYSQL_RES* result = mysql_use_result(&mysql); // 不实际读取
    MYSQL_RES* result = mysql_store_result(&mysql); // 读取实际数据
    if (!result) {
        std::cout << "mysql_use_result faied!" << mysql_error(&mysql) << std::endl;
    }
    
    // 获取表字段
    MYSQL_FIELD *field = 0;
    while(field = mysql_fetch_field(result))
        std::cout << "key: " << field->name << std::endl;
    
    
    // 3. 遍历结果集
    // 获取表字段的数量
    int fnum = mysql_num_fields(result);
    
    MYSQL_ROW row;
    while(row = mysql_fetch_row(result)) {
        unsigned long * lens = mysql_fetch_lengths(result);
        std::cout << "lens: " << std::endl;
        
        for (int i = 0; i < fnum; i++) {
            std::cout << mysql_fetch_field_direct(result, i)->name << ": " << row[i];
            if (row[i])
                std::cout << row[i] << std::endl;
            else
                std::cout << "nullptr" << std::endl;
            
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    
    
    // 4. 清理结果集 (必须)
    mysql_free_result(result);
    
    
    mysql_close(&mysql);
    mysql_library_end();

    return EXIT_SUCCESS;
}