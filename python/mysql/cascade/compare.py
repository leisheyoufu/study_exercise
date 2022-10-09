from __future__ import print_function
from datetime import date, datetime, timedelta
import mysql.connector
import random
import time
import const



def compare_table(table):
    src_cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    src_cursor = src_cnx.cursor()
    sql = "SELECT * FROM %s" % table
    src_cursor.execute(sql)
    src_result = src_cursor.fetchall()
    src_cnx.close()

    dst_cnx = mysql.connector.connect(user=const.DST_USER, password=const.DST_PASSWORD, port=const.DST_PORT, database=const.DST_DB,host=const.DST_HOST)
    dst_cursor = dst_cnx.cursor()
    dst_cursor.execute(sql)
    dst_result = dst_cursor.fetchall()
    dst_cnx.close() 
    if len(src_result) != len(dst_result):
        return "table %s not equal" % table

    if len(src_result) == 0:
        return "table %s compare success" % table

    for i in range(len(src_result)):
        src_row = src_result[i]
        dst_row = dst_result[i]
        if len(src_row) != len(dst_row):
            return "table %s not equal" % table
        for j in range(len(src_row)):
            if src_row[j] != dst_row[j]:
                return "table %s not equal" % table
    return "table %s compare success" % table

if __name__ == "__main__":
    tables = ["customer", "partial_product_order", "product_order", "sub_product_order", "product", "test_main"]
    while(1):
        time.sleep(1)
        for table in tables:
            result = compare_table(table)
            if "success" not in result:
                print(result)

