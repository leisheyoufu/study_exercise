#!/usr/bin/env python
#coding=utf8
import pika
import sys
connection = pika.BlockingConnection(pika.ConnectionParameters(
               'localhost'))
channel = connection.channel()
channel.queue_declare(queue='hello')
def callback(ch, method, properties, body):
    print " [x] Received %r" % (body,)
    sys.exit(0)


channel.basic_consume(callback, queue='hello', no_ack=True)
print ' [*] Waiting for messages. To exit press CTRL+C'
channel.start_consuming()
