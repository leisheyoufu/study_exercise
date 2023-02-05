class Zoo {
public:
    Zoo(int i1, int i2) : d1(i1), d2(i2) {}		// 构造函数
    Zoo(const Zoo&) = delete;		// 拷贝构造
    Zoo(Zoo&&) = default;			// 移动构造
    Zoo& operator=(const Zoo&) = default;		// 拷贝赋值
    Zoo& operator=(const Zoo&&) = delete;		// 移动赋值
    virtual ~Zoo() {}				// 析构函数
private:
    int d1, d2;
};
