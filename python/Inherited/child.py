__author__ = 'chenglong'

import parent

def _hello():
    print "hello this is child module."

class Child(parent.Parent):
    @classmethod
    def _private_hello(cls):
        print 'hello this is private hello from child'

    def hello(self):
        print 'child ----------'
        self._caller()
        print 'child ----------'
    #def hello(self):
    #    _hello()
    #    print "hello this is child class."


if __name__ == '__main__':
    c = Child()
    c.hello()
    p = parent.Parent()
    p.hello()
    c.hello()


