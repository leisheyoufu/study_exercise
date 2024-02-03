g++ -std=c++11  -o deque deque.cc

std::deque 是 c++ 一种序列式容器，其与 vector 类似，其底层内存都是连续的，不同的地方在于， vector 是一端开口，在一端放入数据与扩充空间，而 deque 是双端均开口，都可以放入数据与扩充空间。