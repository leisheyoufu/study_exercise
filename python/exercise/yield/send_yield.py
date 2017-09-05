# -*- coding: utf-8 -*-
def h():
    print 'Wen Chuan',
    m = yield 5  # Fighting!
    print 'in h fuction'
    print m # m is Fighting
    print 'after m'
    d = yield 12
    print 'We are together!' # no chance to print

c = h()
m = c.next()  # m get the parameter 5 from yield 5
d = c.send('m is Fighting!')  #d get 12 from yield 12
print 'We will never forget the date', m, '.', d
