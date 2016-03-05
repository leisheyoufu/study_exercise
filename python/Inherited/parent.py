__author__ = 'chenglong'

def _hello():
    print "hello this is parent module."

class Parent():
    @classmethod
    def _private_hello(cls):
        print 'hello this is private hello from parent'
    @classmethod
    def _caller(cls):
        print 'call parent caller'
        cls._private_hello()
    def hello(self):
        #_hello()
        self._caller()
        print "hello this is parent class."




