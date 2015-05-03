#!/usr/bin/env python
#coding=utf8
import pika, sys

connection = pika.BlockingConnection(pika.ConnectionParameters(
               'localhost'))
channel = connection.channel()

#定义交换机，设置类型为direct
channel.exchange_declare(exchange='messages', type='direct')

#从命令行获取路由键参数，如果没有，则设置为info
routings = sys.argv[1:]
if not routings:
    routings = ['info']

#生成临时队列，并绑定到交换机上，设置路由键
result = channel.queue_declare(exclusive=True)
queue_name = result.method.queue
for routing in routings:
    channel.queue_bind(exchange='messages',
                       queue=queue_name,
                       routing_key=routing)

def callback(ch, method, properties, body):
    print " [x] Received %r" % (body,)

channel.basic_consume(callback, queue=queue_name, no_ack=True)

print ' [*] Waiting for messages. To exit press CTRL+C'
channel.start_consuming()