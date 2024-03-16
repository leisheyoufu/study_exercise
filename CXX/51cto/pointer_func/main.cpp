// main.cpp


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

using namespace std;

#include "function.h"
using namespace funcinfo;


double lineFunc(stack<string> subNodeStack) {

    double bid1 = 10; // for test.
    double ask1 = 20; // for test.
    map<string, double> data = {
        {"bid1", bid1},
        {"ask1", ask1},
    };

    stack<double> valueStack;
    double retValue;
    while (!subNodeStack.empty()) {
        if (funcArity.count(subNodeStack.top())) { // func

            if (funcArity.at(subNodeStack.top()) == ONE_VAR_TYPE) {
                double var1 = valueStack.top();
                valueStack.pop();

                valueStack.push(func1Var.at(subNodeStack.top())(var1)); // 子表达式结果 要入 valueStack 栈
            } else if (funcArity.at(subNodeStack.top()) == TWO_VAR_TYPE) {
                double var1 = valueStack.top();
                valueStack.pop();
                double var2 = valueStack.top();
                valueStack.pop();
                // CL: 这里调用了指针函数
                valueStack.push(func2Var.at(subNodeStack.top())(var1, var2)); // 子表达式结果 要入 valueStack 栈
            }

        } else { // var
            valueStack.push(data[subNodeStack.top()]);
        }

        subNodeStack.pop();
        retValue = valueStack.top();
    }

    return retValue;
}

int main() {
    // read file content.
    ifstream file("names.txt");
    if (!file) {
        cout << "can't open!" << endl;
        exit(0);
    }

    // init func with str.
    string sourceLine;
    while(getline(file, sourceLine)){
        cout << sourceLine << endl;

        string subNodeStr;
        stack<string> subNodeStack; // 存于策略类中的某个变量中
        for (int i = 0; i < sourceLine.size(); ++i) {
            // 过滤行头 & 行尾
            if (sourceLine[i] == '"') {
                if (sourceLine[i+1] == ',')
                    break;
                continue;
            }

            /*
             * 2. 将这部分操作存于策略类的某成员变量; (目前就差打通这步了)
             * 3. 每次行情更新时, 在策略的 update 函数中, 根据新的bid1和ask1时时更新总表达式的结果(即因子值);
             * 4. 上述做完, 将 读取文件 和 生成总表达式的计算方式 的部分移至策略类的on_init部分; (做到策略初始化时只io一次)
             * */
            if (sourceLine[i] == '(' || sourceLine[i] == ')' || sourceLine[i] == ',') {
                if (subNodeStr.empty())
                    continue;
                subNodeStack.push(subNodeStr);
                subNodeStr = "";
                continue;
            }

            subNodeStr += sourceLine[i];
        }

        // TODO: 根据 subNodeStack 内容进行函数匹配, 并进行压栈出栈操作;
        cout << "-----ret-----" << endl;
        cout << lineFunc(subNodeStack) << endl;
        cout << "-------------" << endl;

    }
    file.close();

    return 0;
}