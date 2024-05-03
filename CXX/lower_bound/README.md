lower_bound, upper_bound 是stl中提供的非常实用的函数。其操作对象可以是vector、set以及map。lower_bound返回值一般是 >= 给定val的最小指针（iterator）；upper_bound返回值则是 > 给定val的最小指针（iterator）。

g++ -o main -std=c++14  main1.cpp