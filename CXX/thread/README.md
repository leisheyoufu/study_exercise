https://zhuanlan.zhihu.com/p/72403104
当不获取锁的时候：

diff --git a/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp b/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp
index 9ceb6c4..2e62b4b 100644
--- a/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp
+++ b/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp
@@ -17,10 +17,8 @@ class TestClass{
 
 int main(){
        TestClass test;
-       test.m_mutex.Lock();
        test.m_int = 5;
        cout << "test.m_int:" << test.m_int << endl;
-       test.m_mutex.Unlock();
 
 
        return 0;
编译报错如下：

clang++ ken_thread_safety_annotations.cpp -std=c++11 -Wthread-safety

ken_thread_safety_annotations.cpp:20:7: warning: writing variable 'm_int' requires locking 'test.m_mutex' exclusively [-Wthread-safety-analysis]
        test.m_int = 5;
             ^
ken_thread_safety_annotations.cpp:21:32: warning: reading variable 'm_int' requires locking 'test.m_mutex' [-Wthread-safety-analysis]
        cout << "test.m_int:" << test.m_int << endl;
                                      ^
2 warnings generated.
当获取锁不释放的时候：

diff --git a/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp b/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp
index 9ceb6c4..9f5498d 100644
--- a/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp
+++ b/ken_test/thread_safety_annotation/ken_thread_safety_annotations.cpp
@@ -20,8 +20,6 @@ int main(){
        test.m_mutex.Lock();
        test.m_int = 5;
        cout << "test.m_int:" << test.m_int << endl;
-       test.m_mutex.Unlock();
-
 
        return 0;
 }
编译报错如下：

clang++ ken_thread_safety_annotations.cpp -std=c++11 -Wthread-safety

ken_thread_safety_annotations.cpp:25:1: warning: mutex 'test.m_mutex' is still locked at the end of function [-Wthread-safety-analysis]
}
^
ken_thread_safety_annotations.cpp:20:2: note: mutex acquired here
        test.m_mutex.Lock();
        ^
1 warning generated.