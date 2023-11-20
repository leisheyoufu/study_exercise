constexpr int add(int a, int b) {
    return a + b;
}

int main() {
    constexpr int sum = add(3, 4); // 计算在编译时完成
    return 0;
}