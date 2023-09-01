#include "utils/rangelist.h"
#include <iostream>

int main()
{
    RangeList range;
    range.Add(Interval(1, 5));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(10, 20));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(20, 20));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(20, 21));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(2, 4));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(3, 8));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(10, 10));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(3, 8));
    std::cout << range.ToString() << std::endl;
    range.Add(Interval(10, 10));
    std::cout << range.ToString() << std::endl;
    range.Remove(Interval(10, 11));
    std::cout << range.ToString() << std::endl;
    range.Remove(Interval(15, 17));
    std::cout << range.ToString() << std::endl;
    range.Remove(Interval(3, 19));
    std::cout << range.ToString() << std::endl;
    return 0;
}