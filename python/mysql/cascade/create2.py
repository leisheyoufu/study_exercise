from __future__ import print_function

import mysql.connector
from mysql.connector import errorcode
import const

DB_NAME = 'foreign_key3'

PRODUCT = """
 CREATE TABLE product_%(index)s (
    category INT NOT NULL, id INT NOT NULL,
    price DECIMAL,
    PRIMARY KEY(category, id)
)   ENGINE=INNODB;
"""

CUSTOMER = """
    CREATE TABLE customer_%(index)s (
    id INT NOT NULL,
    PRIMARY KEY (id)
)   
"""
PRODUCT_ORDER = """
    CREATE TABLE product_order_%(index)s (
    no INT NOT NULL AUTO_INCREMENT,
    product_category INT NOT NULL,
    product_id INT NOT NULL,
    customer_id INT NOT NULL,

    PRIMARY KEY(no),
    INDEX (product_category, product_id),
    INDEX (customer_id),

    FOREIGN KEY (product_category, product_id)
      REFERENCES product_%(index)s(category, id)
      ON UPDATE CASCADE ON DELETE CASCADE,

    FOREIGN KEY (customer_id)
      REFERENCES customer_%(index)s(id) ON UPDATE CASCADE ON DELETE CASCADE
)   ENGINE=INNODB;
"""

SUB_PRODUCT_ORDER = """
CREATE TABLE sub_product_order_%(index)s (
    no INT NOT NULL AUTO_INCREMENT,
    sub_no INT NOT NULL,
    product_category INT NOT NULL,
    product_id INT NOT NULL,
    v INT NOT NULL,
    PRIMARY KEY(no),
    FOREIGN KEY (sub_no)
      REFERENCES product_order_%(index)s(no)
      ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY(product_category, product_id)
      REFERENCES product_%(index)s(category, id)  
      ON UPDATE CASCADE ON DELETE CASCADE
)   ENGINE=INNODB;
"""

PARTIAL_PRODUCT_ORDER = """
CREATE TABLE partial_product_order_%(index)s (
    no INT NOT NULL AUTO_INCREMENT,
    customer_id INT NOT NULL,
    PRIMARY KEY(no),
    FOREIGN KEY (customer_id)
      REFERENCES product_order_%(index)s(customer_id)
      ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=INNODB;
"""

TEST_MAIN = """
CREATE TABLE test_main_%(index)s(
  id      INT,
  value   VARCHAR(10),
  PRIMARY KEY(id)
);

"""


def create_database(cursor):
    try:
        cursor.execute(
            "CREATE DATABASE {} DEFAULT CHARACTER SET 'utf8'".format(DB_NAME))
    except mysql.connector.Error as err:
        print("Failed creating database: {}".format(err))
        exit(1)

def create_table(cursor):
    for i in range(100):
        product = PRODUCT % {"index": i}
        customer = CUSTOMER % {"index": i}
        product_order = PRODUCT_ORDER % {"index": i}
        sub_product_order = SUB_PRODUCT_ORDER % {"index": i}
        partial_product_order = PARTIAL_PRODUCT_ORDER % {"index": i}
        test_main = TEST_MAIN % {"index": i}

        queries = [product, customer, product_order, sub_product_order, partial_product_order, test_main]
        for query in queries:
            try:
                # print("Creating table {}: ".format(table_name), end='')
                cursor.execute(query)
            except mysql.connector.Error as err:
                if err.errno == errorcode.ER_TABLE_EXISTS_ERROR:
                    print("already exists.")
                else:
                    print(err.msg)
            else:
                print("OK")




if __name__ == "__main__":
    cnx = mysql.connector.connect(user=const.SRC_USER, password=const.SRC_PASSWORD, port=const.SRC_PORT, host=const.SRC_HOST)
    cursor = cnx.cursor()
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
    create_table(cursor)
    cursor.close()
    cnx.close()