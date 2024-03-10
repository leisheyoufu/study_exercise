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
    
    
    // 创建表
    string sql = "create table `t_image` (
        `id` int AUTO_INCREMENT, \
        `name` varchar(1024), \
        `path` varchar(2048), \
        `size` int, \
        PRIMARY KEY(`id`)
    )";
    int ret = mysql_query(&mysql, sql.c_str());
    if (ret != 0) { // 出错
        std::cout << "mysql_query faied! " << mysql_error(&mysql) << std::endl;
    }
    
    
    // 插入数据
    for (int i = 0; i < 1000; i++) {
        stringstream insert_sql;
        insert_sql << "insert `t_image` (`name`,`path`,`size`) values('test"
        insert_sql << i << ".jpg','d:/img/test.jpg',10240)"
        
        int ret = mysql_query(&mysql, sql.c_str());
        if (ret == 0) { // 成功
            int count = mysql_affected_rows(&mysql);
            std::cout << "mysql_affected_rows: " << count << ", current id: " << mysql_insert_id(&mysql) << std::endl;
        } else {
            std::cout << "mysql_query faied! " << mysql_error(&mysql) << std::endl;
        }
    }
    
    
    // 修改数据
    string update_sql = "update t_image set `name`='test3.png',size=2000 where id=1";
    int update_ret = mysql_query(&mysql, sql.c_str());
    
    if (update_ret == 0) {
        int count = mysql_affected_rows(&mysql);
        std::cout << "update mysql_affected_rows: " << count << std::endl;
    } else {
        std::cout << "update failed!" << mysql_error(&mysql) << std::endl;
    }
    
    
    map<string, string> keyValues;
    
    keyValues.insert(make_pair("name", "image_update001.jpg"));
    keyValues.insert(make_pair("size", 5000));
    string where = "where id=1";
    
    string temp = "";
    for (auto iterator = keyValues.begin(); iterator != keyValues.end(); iterator++) {
        temp += "`";
        temp += iterator->first;
        temp += "`='"
        temp += iterator->second;
        temp += "',"
    }
    temp += "id=id";
    sql = "update t_image set";
    sql += temp;
    sql += where;
    
    
    
    // 删除数据
    // string delete_sql = "truncate t_image"; // 清空数据, 并恢复自增id从1开始
    string delete_sql = "delete from t_image"; // delete 不会实际删除数据库的空间
    int delete_ret = mysql_query(&mysql, delete_sql.c_str());
    
    if (delete_ret == 0) {
        int count = mysql_affected_rows(&mysql);
        std::cout << "delete mysql_affected_rows: " << count << endl;
    } else {
        std::cout << "delete failed! " << mysql_error(&mysql) << std::endl;
    }
    delete_sql = "OPTIMIZE TABLE t_image"; // 优化删除, 会清理数据库空间
    delete_ret = mysql_query(&mysql, delete_sql.c_str());
    
    
    mysql_close(&mysql);
    mysql_library_end();

    return EXIT_SUCCESS;
}