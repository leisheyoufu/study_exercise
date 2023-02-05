void foo() noexcept {
  // ...
}

void swap(Type& x, Type& y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

struct Base {
  virtual void vfunc(float) { }
};

struct Derived: Base {
  // virtual void vfunc(int) { }
  virtual void vfunc(int)	override { }
}

struct Base final {};

struct Derived: Base {};			// Error

struct Base {
  virtual void func() final;
}

struct Derived : Base {
  void func();			// Error
}

/*
子类 Derived 在继承父类 Base 之后想要重写父类的 void vfunc(float) 方法，但是我们知道，要重写父类方法需要函数签名完全一致，这里可能由于疏忽大意，将参数类型写为了 int。这就导致子类的这个函数定义了一个新函数，而非是期望中的对于父类函数的重写了。而编译器肯定是不知道你其实是想重写父类方法的，因为你函数签名的不一致，就按照一个新方法来处理了。

在 C++11 之后，引入了 override 关键字，在你确实想要重写的函数之后，加上这个关键字，编译器会在你在想重写但是函数签名写错的时候提醒你，这个被标记为重写函数的函数实际上并未进行重写。

*/