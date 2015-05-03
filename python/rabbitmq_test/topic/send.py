#!/usr/bin/env python
#coding=utf8
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(
               'localhost'))
channel = connection.channel()

#定义交换机，设置类型为topic
channel.exchange_declare(exchange='messages', type='topic')

#定义路由键
routings = ['happy.work', 'happy.life', 'sad.work', 'sad.life']

#将消息依次发送到交换机，并设定路由键
for routing in routings:
    message = '%s message.' % routing
    channel.basic_publish(exchange='messages',
                          routing_key=routing,
                          body=message)
    print message

connection.close()