from __future__ import print_function
from datetime import date, datetime, timedelta
import mysql.connector
import random
import time
import const
import string

import multiprocessing
from multiprocessing import Process
from multiprocessing import queues


def random_str(n):
    alphabet = string.ascii_letters + string.digits
    password = ''.join(random.choice(alphabet) for i in range(n))
    return password

def insert_customer():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    cursor = cnx.cursor()
    count = 10000
    add_customer = ("INSERT INTO customer (id) VALUES (%(id)s)")
    data_customers = []
    for i in range(count):
        data_customer = {'id': i}
        data_customers.append(data_customer)
    cursor.executemany(add_customer, data_customers)
    cnx.commit()
    cursor.close()
    cnx.close()

def update_customer(cnx):
    cursor = cnx.cursor()
    update = ("UPDATE customer SET id=id+100000 WHERE id>7000")
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
    count = 3000
    desc = ("INSERT INTO customer (id) VALUES (%(id)s)")
    items = []
    for i in range(count):
        item = {'id': i+7001}
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    cursor.close()

def insert_product():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    cursor = cnx.cursor()
    count = 200000
    desc = ("INSERT INTO product (category, id, price) VALUES (%(category)s, %(id)s, %(price)s)")
    items = []
    for i in range(count):
        item = {
            'category': i,
            'id': i,
            'price': 1.0 +i
        }
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    cursor.close()
    cnx.close()

def insert_product_order():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    cursor = cnx.cursor()
    count = 10000
    desc = ("INSERT INTO product_order (product_category, product_id, customer_id) VALUES (%(product_category)s, %(product_id)s, %(customer_id)s)")
    items = []
    for i in range(count):
        item = {
            'product_category': i,
            'product_id': i,
            'customer_id': i
        }
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    cursor.close()
    cnx.close()

def insert_sub_product_order():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    cursor = cnx.cursor()
    count = 10000
    desc = ("INSERT INTO sub_product_order (sub_no, product_category, product_id, v) VALUES (%(sub_no)s, %(product_category)s, %(product_id)s, %(v)s)")
    items = []
    for i in range(count):
        item = {
            'sub_no': i + 1,
            'product_category': i,
            'product_id': i,
            'v': i
        }
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    cursor.close()
    cnx.close()

def insert_partial_product_order():
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    cursor = cnx.cursor()
    count = 10000
    desc = ("INSERT INTO partial_product_order (customer_id) VALUES (%(customer_id)s)")
    items = []
    for i in range(count):
        item = {
            'customer_id': i
        }
        items.append(item)
    cursor.executemany(desc, items)
    cnx.commit()
    cursor.close()
    cnx.close()   

def task(func):
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    func(cnx)
    cnx.close()

if __name__ == "__main__":
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, database=const.SRC_DB,host=const.SRC_HOST)
    #insert_customer()
    insert_product()
    #insert_product_order()
    #insert_sub_product_order()
    #insert_partial_product_order()
    #update_customer(cnx)

    # funcs = [insert_customer, insert_product, insert_product_order, insert_sub_product_order, insert_partial_product_order]
    # for func in funcs:
    #     p = Process(target=func)
    #     p.start()
    cnx.close()
    