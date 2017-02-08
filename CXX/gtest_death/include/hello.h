 #ifndef SRC_HELLO_H_
 #define SRC_HELLO_H_

 #include<string>

namespace death {

 class HelloWorld
 {
 public:
     HelloWorld();
     // virtual ~HelloWorld();
     std::string SayHello();
     void Die();
 };
 }

 #endif /* SRC_HELLOWORLD_H_ */
