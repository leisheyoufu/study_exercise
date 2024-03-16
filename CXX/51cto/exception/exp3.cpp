// 异常的多态使用
#include <iostream>

using namespace std;

class BaseException {

public:
  virtual void printError() {
    cout << "BaseException printError" << endl;
  }

};

class NullPointerException: public BaseException {
  
public:
  virtual void printError() {
    cout << "NullPointerException printError" << endl;
  }

};

class OutOfRangeException: public BaseException {

public:
  virtual void printError() {
    cout << "OutOfRangeException printError" << endl;
  }

};


void doWork() {
  //throw NullPointerException();
  throw OutOfRangeException();
}


void test01() {

  try {
    doWork();
  }
  catch(BaseException &baseException) {
    baseException.printError();
  }
  catch (NullPointerException &nullPointerException) {
    nullPointerException.printError();
  }
  catch (OutOfRangeException &outOfRangeException) {
    outOfRangeException.printError();
  }
  catch (...) {
    cout << "... 异常" << endl;
  }
}


int main() {

  test01();

  return EXIT_SUCCESS;
}

/*
OutOfRangeException printError

*/