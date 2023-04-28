#include<iostream>
#include<vector>

// using namespace std;
struct Base {
    // 创建一个虚函数
    virtual void bar() { std::cout << "Base::bar()\n"; }
    virtual ~Base() = default;
    
    std::string val;
};

struct Derived : Base {
    Derived() { std::cout << "Derived::Constructor\n"; }
    ~Derived() { std::cout << "Derived::Descontructor\n"; }
    void bar() override { std::cout << "Derived::bar()\n"; }

    std::string val;
};

int main()
{
    std::cout << "\nunique_ptr 指向对象的所有权的测试---->\n";
    {
        // ptr_Derived拥有对象的所有权
        auto ptr_Derived = std::make_unique<Derived> ();
        ptr_Derived->val = "unique_ptr";
        auto ptr_MoveD = std::move(ptr_Derived);    //ptr_Derived 不在拥有对象所有权

        assert(!ptr_Derived);    //ptr_Derived为empty
        ptr_MoveD->bar();
        std::cout << ptr_MoveD->val << std::endl;
        // 这里将会调用一次Derived的析构函数
    }

    std::cout << "\n多态运行时测试----->\n";
    {
        std::unique_ptr<Base> p_base = std::make_unique<Derived>();    // p_base是指向基类的指针，但是占有D的unique_ptr
        p_base->bar();    // 这里将调用的Derived的bar函数

        std::vector<std::unique_ptr<Base>> v;    // 容器也可以存储unique_ptr对象

        v.push_back(std::move(p_base));
        v.push_back(std::make_unique<Derived>());
        v.emplace_back(new Derived);

        for (auto& itr : v)
        {
            itr->bar();
        }

        // 这里将调用3次析构函数 
    }

    std::cout << "\n数组形式的unique_str对象测试--->\n";
    {
        std::unique_ptr<Derived[]> parr{ new Derived[4] };
        // 这里将调用4次析构函数
    }
    return 0;
}

/*
unique_ptr 指向对象的所有权的测试---->
Derived::Constructor
Derived::bar()
unique_ptr
Derived::Descontructor

多态运行时测试----->
Derived::Constructor
Derived::bar()
Derived::Constructor
Derived::Constructor
Derived::bar()
Derived::bar()
Derived::bar()
Derived::Descontructor
Derived::Descontructor
Derived::Descontructor

数组形式的unique_str对象测试--->
Derived::Constructor
Derived::Constructor
Derived::Constructor
Derived::Constructor
Derived::Descontructor
Derived::Descontructor
Derived::Descontructor
Derived::Descontructor
*/