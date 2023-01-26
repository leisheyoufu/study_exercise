#ifndef FBC_MESSY_TEST_EXPLICIT_HPP
#define FBC_MESSY_TEST_EXPLICIT_HPP
 
// reference Bjarne Stroustrup sample
class String{
public:
	explicit String(int n) {};
	String(const char *p) {};
};
 
void test_explicit();
 
#endif // FBC_MESSY_TEST_EXPLICIT_HPP

static void test1()
{
	//String s1 = 'a'; // 错误：不能做隐式char->String转换
	String s2(10); // 可以：调用explicit String(int n);
	String s3 = String(10); // 可以：调用explicit String(int n);再调用默认的复制构造函数
	String s4 = "Brian"; // 可以：隐式转换调用String(const char *p);再调用默认的复制构造函数
	String s5("Fawlty"); // 可以：正常调用String(const char *p);
}
 
static void f(String)
{
 
}
 
static String g()
{
	//f(10); // 错误：不能做隐式int->String转换
	f("Arthur"); // 可以：隐式转换，等价于f(String("Arthur"));
	//return 10; // 错误同上
    return String(10); // cl: 可以显示转换
}
 
int main()
{
	test1();
	g();
    return 0;
}