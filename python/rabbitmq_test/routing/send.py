#!/usr/bin/env python
#coding=utf8
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(
               'localhost'))
channel = connection.channel()

#定义交换机，设置类型为direct
channel.exchange_declare(exchange='messages', type='direct')

#定义三个路由键
routings = ['info', 'warning', 'error']

#将消息依次发送到交换机，并设置路由键
for routing in routings:
    message = '%s message.' % routing
    channel.basic_publish(exchange='messages',
                          routing_key=routing,
                          body=message)
    print message

connection.close()