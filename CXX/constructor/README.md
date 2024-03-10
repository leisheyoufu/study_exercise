
g++ -fexec-charset=GBK -o main copy.cpp

构造函数调用顺序： 先执行基类，后执行派生类
析构函数调用谁徐： 先执行派生类后执行基类

这个时候，如果析构函数是一个普通函数，那么delete的时候就不会访问虚函数表。而是直接析构father的实际析构函数地址。会造成子类的析构函数无法调用，造成内存泄漏。

如果析构函数是一个虚函数，那么delete的时候就会访问虚函数表，该虚函数表是son的。所以会调用son的虚函数，然后再调用father的。

所以，析构函数之所以推荐成虚函数，就是希望在继承之后，父类指针可以访问到析构函数。从而完成由父类指针完成子类和父类的析构。如果不是虚函数，容易造成子类的内存泄漏

## reference
https://blog.csdn.net/cdlwhm1217096231/article/details/89204718
https://zhuanlan.zhihu.com/p/638679294?utm_id=0