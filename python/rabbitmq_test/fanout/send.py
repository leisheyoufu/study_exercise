#!/usr/bin/env python
#coding=utf8
import pika
 
connection = pika.BlockingConnection(pika.ConnectionParameters(
               'localhost'))
channel = connection.channel()
 
#定义交换机
channel.exchange_declare(exchange='messages', type='fanout')
 
#将消息发送到交换机
channel.basic_publish(exchange='messages', routing_key='', body='Hello World!')
print " [x] Sent 'Hello World!'"
connection.close()
