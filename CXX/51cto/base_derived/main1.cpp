// 继承的基础
#include <iostream>

using namespace std;

class BaseWeb {

public:
  void header() {
    cout << "公共头部" << endl;
  }

  void footer() {
    cout << "公共底部" << endl;
  }

  void left() {
    cout << "左侧列表" << endl;
  }

};

class News: public BaseWeb { // 继承

public:

  void content() {
    cout << "新闻播放" << endl;
  }

};

class Entertainment: public BaseWeb {

public:

  void content() {
    cout << "白百合..." << endl;
  }

};

class Game : public BaseWeb {

public:
  void content() {
    cout << "KPL 直播" << endl;
  }
};

void test01() {

  News news;
  news.header();
  news.footer();
  news.content();

  Entertainment entertainment;
  entertainment.header();
  entertainment.footer();
  entertainment.content();
}

int main() {

  test01();

  return EXIT_SUCCESS;
}

/*
公共头部
公共底部
新闻播放
公共头部
公共底部
白百合
*/