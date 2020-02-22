def h():
    print ('Wen Chuan'),
    m = yield 5  # Fighting!
    print (m)
    d = yield 12
    print ('We are together!')

c = h()
m = c.__next__()  #m 获取了yield 5 的参数值 5
d = c.send('Fighting!')  #d 获取了yield 12 的参数值12
print ('We will never forget the date', m, '.', d)

"""
Output:
Wen Chuan
Fighting!
We will never forget the date 5 . 12
"""