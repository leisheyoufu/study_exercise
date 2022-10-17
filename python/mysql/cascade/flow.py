from __future__ import print_function
from datetime import date, datetime, timedelta
import mysql.connector
import random
import time
import const

import multiprocessing
from multiprocessing import Process
from multiprocessing import queues


CREATE_TEST_DDL = """
CREATE TABLE test_ddl
(
  id INT(11) AUTO_INCREMENT PRIMARY KEY, 
  name VARCHAR(24),
  dept_id INT(11),
  salary FLOAT
) ENGINE=innodb;
"""

INSERT_TEST_DDL1 = """
insert into test_ddl values(3, "red", 1001, 33347.8);
"""

ALERT_TEST_DDL = """
ALTER TABLE test_ddl ADD COLUMN c2 INT, ADD COLUMN c3 INT;
"""

INSERT_TEST_DDL2 = """
insert into test_ddl values(4, "blue", 1002, 53347.8, 500, 4000);
"""

DROP_TEST_DDL = """
drop table test_ddl;
"""

def update_customer(cnx):
    cursor = cnx.cursor()
    update = ("UPDATE customer SET id=id+100000 WHERE id>7000 AND id<7105")
    cursor.execute(update)
    cnx.commit()
    cursor.close()

def delete_customer(cnx):
    cursor = cnx.cursor()
    delete = ("delete from customer WHERE id>107000")
    cursor.execute(delete)
    cnx.commit()
    cursor.close()

def insert_customer2(cnx):
    cursor = cnx.cursor()
    count = 4
    desc = ("INSERT INTO customer (id) VALUES (%(id)s)")
    items = []
    for i in range(count):
        item = {'id': i+7001}
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    cursor.close()

def update_product_order(cnx):
    cursor = cnx.cursor()
    update = ("UPDATE product_order SET no=0 WHERE no=1000")
    cursor.execute(update)
    cnx.commit()
    update = ("UPDATE product_order SET no=1000 WHERE no=0")
    cursor.close()

def delete_insert_product_order(cnx):
    cursor = cnx.cursor()
    delete = ("delete from product_order WHERE product_id>=1001 AND product_id<=1200")
    cursor.execute(delete)
    cnx.commit()
    time.sleep(1)
    count = 200
    desc = ("INSERT INTO product_order (product_category, product_id, customer_id) VALUES (%(product_category)s, %(product_id)s, %(customer_id)s)")
    items = []
    for i in range(count):
        item = {
            'product_category': i+1000 +1,
            'product_id': i+1000 +1,
            'customer_id': i+1000 +1
        }
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    cursor.close()

def delete_insert_test_main(cnx):
    cursor = cnx.cursor()
    count = 200
    desc = ("INSERT INTO test_main (id, value) VALUES (%(id)s, %(value)s)")
    items = []
    for i in range(count):
        item = {
            'id': i,
            'value': 's-%d' % i
        }
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    time.sleep(1)
    delete = ("delete from test_main;")
    cursor.execute(delete)
    cnx.commit()
    cursor.close()

def ddl_test_ddl(cnx):
    cursor = cnx.cursor()
    query = (CREATE_TEST_DDL)
    cursor.execute(query)
    query = (INSERT_TEST_DDL1)
    cursor.execute(query)
    cnx.commit()
    query = (ALERT_TEST_DDL)
    cursor.execute(query)
    query = (INSERT_TEST_DDL2)
    cursor.execute(query)
    cnx.commit()
    query = (DROP_TEST_DDL)
    cursor.execute(query)


def customer_task():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    count = 1
    while(1):
        update_customer(cnx)
        time.sleep(1)
        delete_customer(cnx)
        time.sleep(1)
        insert_customer2(cnx)
        time.sleep(1)
        print("update customer task is running %d" % count)
        count+=1
    cnx.close()

def product_order_task():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    count = 1
    while(1):
        update_product_order(cnx)
        delete_insert_product_order(cnx)
        time.sleep(1)
        print("update product_order task is running %d" % count)
        count+=1
    cnx.close()

def test_main_task():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    count = 1
    while(1):
        delete_insert_test_main(cnx)
        time.sleep(5)
        print("update test_main task is running %d" % count)
        count+=1
    cnx.close() 

def test_ddl_task():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    count = 1
    while(1):
        ddl_test_ddl(cnx)
        time.sleep(1)
        print("ddl test_ddl task is running %d" % count)
        count+=1
    cnx.close() 

if __name__ == "__main__":
    funcs = [customer_task, product_order_task, test_main_task, test_ddl_task]
    for func in funcs:
        p = Process(target=func)
        p.start()
    