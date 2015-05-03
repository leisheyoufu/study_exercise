#!/usr/bin/env python
#coding=utf8
import pika

#连接rabbitmq服务器
connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()

#定义队列
channel.queue_declare(queue='compute_queue')
print ' [*] Waiting for n'

#将n值加1
def increase(n):
    return n + 1

#定义接收到消息的处理方法
def request(ch, method, props, body):
    print " [.] increase(%s)"  % (body,)

    response = increase(int(body))

    #将计算结果发送回控制中心，增加correlation_id的设定
    ch.basic_publish(exchange='',
                     routing_key=props.reply_to,
                     properties=pika.BasicProperties(correlation_id = \
                                                     props.correlation_id),
                     body=str(response))
    ch.basic_ack(delivery_tag = method.delivery_tag)

channel.basic_qos(prefetch_count=1)
channel.basic_consume(request, queue='compute_queue')

channel.start_consuming()