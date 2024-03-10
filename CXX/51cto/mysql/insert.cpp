#include <iostream>
#include <mysql.h>
#include <chrono> // 计时库

using namespace std;
using namespace chrono;

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


    // 创建表
    string sql = "create table `t_video` (
        `id` int AUTO_INCREMENT, \
        `name` varchar(1024), \
        `path` varchar(2048), \
        `size` int, \
        PRIMARY KEY(`id`)
    ) ENGINE=InnoDB;"; // 设置支持事务回滚的 InnoDB 引擎
    int ret = mysql_query(&mysql, sql.c_str());

    
    // 事务
    // 1. 开始事务
    // START transaction
    sql = "START transaction";
    int ret = mysql_query(&mysql, sql.c_str());
    if (ret != 0) // 出错
        std::cout << "mysql_query faied! " << mysql_error(&mysql) << std::endl;
    
    
    // 2. 设置为手动提交事务
    // set autocommit = 0
    sql = "set autocommit = 0";
    int ret = mysql_query(&mysql, sql.c_str());
    if (ret != 0) // 出错
        std::cout << "mysql_query faied! " << mysql_error(&mysql) << std::endl;
        
    
    // 3. sql语句
    for (int i = 0; i < 3; i++) {
        sql = "insert into t_video(name) values('test three!')";
        int ret = mysql_query(&mysql, sql.c_str());
        if (ret != 0)
            cout << "mysql_query faied! " << mysql_error(&mysql) << endl;
    }
    
    
    // 4. 回滚rollback
    sql = "rollback";
    ret = mysql_query(&mysql, sql.c_str());
    if (ret != 0)
        cout << "mysql_query failed: " << mysql_error(&mysql) << endl; 
    
    
    // 5. COMMIT
    sql = "COMMIT"; // 提交事务
    ret = mysql_query(&mysql, sql.c_str());
    if (ret != 0)
        cout << "mysql_query failed: " << mysql_error(&mysql) << endl;
    
    
    // 6. 恢复自动提交 set autocommit = 1
    sql = "set autocommit = 1";
    ret = mysql_query(&mysql, sql.c_str());
    if (ret != 0)
        cout << "mysql_query failed: " << mysql_error(&mysql) << endl;
    
    
    sql = "select count(*) from t_video(name) values('test here!')";
    ret = mysql_query(&mysql, sql.c_str());
    if (ret != 0)
        cout << "mysql_query failed: " << mysql_error(&mysql) << endl; 
    
    MYSQL_RES *res = mysql_store_result(&mysql);
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row)
            cout << "t_video count(*) = " << row[0] << endl;            
    }
    
    
    
    
    // 单条语句插入10000条数据;
    auto start = system_clock::now()
    for (int i = 0; i < 1000; i++) {
        sql = "insert into t_video(name, path) values('single', '0123456789')"
        ret = mysql_query(&mysql, sql.c_str());
        if (ret != 0) 
            cout << "mysql_error failed: " << mysql_error(&mysql) << endl;
    }
    auto end = system_clock::now()
    
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "单条语句插入10000条数据 duration: " << duration.count() << endl;

    
    // 多条语句插入10000条数据;
    {
        auto start = system_clock::now()
        sql = ""
        for (int i = 0; i < 1000; i++)
            sql += "insert into t_video(name, path) values('single', '0123456789');"
        
        ret = mysql_query(&mysql, sql.c_str());
        if (ret != 0) 
            cout << "mysql_error failed: " << mysql_error(&mysql) << endl;
        
        do {
            cout << mysql_affected_rows(&mysql) << endl; // 返回前一次 MySQL 操作所影响的记录行数
        } while(mysql_next_result(&mysql) == 0)
        
        auto end = system_clock::now()
        
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "单条语句插入10000条数据 duration: " << duration.count() << endl;
    }
    
        
    mysql_close(&mysql);
    mysql_library_end();

    return EXIT_SUCCESS;
}