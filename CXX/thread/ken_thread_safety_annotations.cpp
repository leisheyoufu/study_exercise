/**********************************************
 *requist: yum install clang/apt-get install clang
 *command: clang++ ken_thread_safety_annotations.cpp -std=c++11 -Wthread-safety
 *detailed information: Thread Safety Analysis
**********************************************/

#include <iostream>
#include "mutex_lockable.h"

using namespace std;

class TestClass{
	public:
		Mutex m_mutex;
		int m_int GUARDED_BY(m_mutex);
};

int main(){
	TestClass test;
	test.m_mutex.Lock();
	test.m_int = 5;
	cout << "test.m_int:" << test.m_int << endl;
	test.m_mutex.Unlock();


	return 0;
}