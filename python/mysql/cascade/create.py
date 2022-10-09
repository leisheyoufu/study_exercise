from __future__ import print_function

import mysql.connector
from mysql.connector import errorcode
import const

DB_NAME = 'foreign_key'

TABLES = {}
TABLES['product'] = (
    """
    CREATE TABLE product (
    category INT NOT NULL, id INT NOT NULL,
    price DECIMAL,
    PRIMARY KEY(category, id)
)   ENGINE=INNODB;
""")

TABLES['customer'] = (
    """
    CREATE TABLE customer (
    id INT NOT NULL,
    PRIMARY KEY (id)
)   
""")

TABLES['product_order'] = (
    """
    CREATE TABLE product_order (
    no INT NOT NULL AUTO_INCREMENT,
    product_category INT NOT NULL,
    product_id INT NOT NULL,
    customer_id INT NOT NULL,

    PRIMARY KEY(no),
    INDEX (product_category, product_id),
    INDEX (customer_id),

    FOREIGN KEY (product_category, product_id)
      REFERENCES product(category, id)
      ON UPDATE CASCADE ON DELETE CASCADE,

    FOREIGN KEY (customer_id)
      REFERENCES customer(id) ON UPDATE CASCADE ON DELETE CASCADE
)   ENGINE=INNODB;
""")

TABLES['sub_product_order'] = (
"""
CREATE TABLE sub_product_order (
    no INT NOT NULL AUTO_INCREMENT,
    sub_no INT NOT NULL,
    product_category INT NOT NULL,
    product_id INT NOT NULL,
    v INT NOT NULL,
    PRIMARY KEY(no),
    FOREIGN KEY (sub_no)
      REFERENCES product_order(no)
      ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY(product_category, product_id)
      REFERENCES product(category, id)  
      ON UPDATE CASCADE ON DELETE CASCADE
)   ENGINE=INNODB;
""")

TABLES['partial_product_order'] = (
"""
CREATE TABLE partial_product_order (
    no INT NOT NULL AUTO_INCREMENT,
    customer_id INT NOT NULL,
    PRIMARY KEY(no),
    FOREIGN KEY (customer_id)
      REFERENCES product_order(customer_id)
      ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=INNODB;
""")

TABLES['test_main'] = (
    """
    CREATE TABLE test_main(
  id      INT,
  value   VARCHAR(10),
  PRIMARY KEY(id)
);
"""
)

cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, host=const.SRC_HOST)
cursor = cnx.cursor()

def create_database(cursor):
    try:
        cursor.execute(
            "CREATE DATABASE {} DEFAULT CHARACTER SET 'utf8'".format(DB_NAME))
    except mysql.connector.Error as err:
        print("Failed creating database: {}".format(err))
        exit(1)

try:
    cursor.execute("USE {}".format(DB_NAME))
except mysql.connector.Error as err:
    print("Database {} does not exists.".format(DB_NAME))
    if err.errno == errorcode.ER_BAD_DB_ERROR:
        create_database(cursor)
        print("Database {} created successfully.".format(DB_NAME))
        cnx.database = DB_NAME
    else:
        print(err)
        exit(1)

for table_name in TABLES:
    table_description = TABLES[table_name]
    try:
        print("Creating table {}: ".format(table_name), end='')
        cursor.execute(table_description)
    except mysql.connector.Error as err:
        if err.errno == errorcode.ER_TABLE_EXISTS_ERROR:
            print("already exists.")
        else:
            print(err.msg)
    else:
        print("OK")

cursor.close()
cnx.close()