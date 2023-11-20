class Circle {
public:
    constexpr Circle(double r) : radius(r) {}
    constexpr double area() const {
        return 3.14159265358979323846 * radius * radius;
    }

private:
    double radius;
};

int main() {
    constexpr Circle c(5.0); // 计算在编译时完成
    return 0;
}