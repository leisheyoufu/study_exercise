#include<deque>
#include<iostream>
 
template<typename T>
void printDeque(std::deque<T>& tmp_deque)
{
    for(auto iter = tmp_deque.begin(); iter != tmp_deque.end(); iter++)
    {
        std::cout << *iter <<" ";
    }
    std::cout <<"" << std::endl;
}
 
int main()
{
    std::deque<int> tmp_deque2;
    tmp_deque2 = {1, 2 , 3, 4, 5, 6};
    printDeque(tmp_deque2);
    tmp_deque2.push_back(22);
    tmp_deque2.push_front(33);
    std::cout << tmp_deque2.front() << std::endl;
    std::cout << tmp_deque2.back() << std::endl;
    printDeque(tmp_deque2);
    tmp_deque2.pop_back();
    tmp_deque2.pop_front();
    std::cout << tmp_deque2.front() << std::endl;
    std::cout << tmp_deque2.back() << std::endl;
    printDeque(tmp_deque2);
    tmp_deque2.clear();
    std::cout << tmp_deque2.empty() << std::endl;
    return 0;
}