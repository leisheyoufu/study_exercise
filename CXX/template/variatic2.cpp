#include<iostream>
#include<string>

template<typename... Types> class Tup;
template<> class Tup<> {};
template<typename Head,typename... Tail>
class Tup<Head, Tail...> :public Tup<Tail...>{
	typedef Tup<Tail...> Base;
protected:
	Head m_head;
public:
	Tup() {}
	Tup(Head h,Tail... t):m_head(h),Base(t...){}
	Head& head() { return m_head; }
	Base& tail() { return *this; }//这里用到了一个很有意思的转型技巧，*this相当于子类对象，返回值类型Base为父类类型，子类转父类（向上类型转换）会出现成员收缩。即类型转换为父类对象后，父类对象不再具备访问原有子类对象新成员的权力，而只能访问父类本身已有的成员。在这里返回对象的指针相当于指向了头部元素的下一个元素
};

int main() {
    Tup<int, std::string, double> tupl(1, "234", 5.0);
    std::cout << tupl.head() << " " << tupl.tail().head() << " " << tupl.tail().tail().head() << std::endl;

}