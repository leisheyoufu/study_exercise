#include <iostream>
using namespace std;

// 适用avg这种两个参数的函数
string getWholeExpression(string func_name, string line, int& begin, int& period, string& alpha) {

    string periodStr, alphaStr;
    bool isPeriod = true;
    for (int i = begin + 1; i < line.size(); i++) {
        if (line[i] == ')')
            break;

        if (line[i] == ',') {
            isPeriod = !isPeriod;
            continue;
        }

        isPeriod ? (periodStr += line[i]) : (alphaStr += line[i]);
    }

    string ret = func_name + '(' + periodStr + ',' + alphaStr + ')';

    // modify outside value.
    period = atoi(periodStr.c_str());
    alpha = string(alphaStr);

    begin += ret.size();

    return ret;
}

// 适用ema这种三个参数的函数
string getWholeExpression(string func_name, string line, int& begin, int& period, double& rate, string& alpha) {
    string periodStr, rateStr, alphaStr;
    int nodeIndex = 0;
    for (int i = begin + 1; i < line.size(); i++) {
        if (line[i] == ')')
            break;

        if (line[i] == ',') {
            nodeIndex++;
            continue;
        }

        switch (nodeIndex) {
            case 0:{
                periodStr += line[i];
                break;
            }
            case 1:{
                rateStr += line[i];
                break;
            }
            case 2:{
                alphaStr += line[i];
                break;
            }
        }
    }
    string ret = func_name + '(' + periodStr + ',' + rateStr + ',' + alphaStr + ')';

    period = stoi(periodStr.c_str());
    alpha = string(alphaStr);
    rate = atof(rateStr.c_str());

    begin += ret.size();

    return ret;
}

int main() {

    string target1 = "add(avg(10,VOI),div(bid1,ask1))";
    string target2 = "add(ema(10,0.2,VOI),div(bid1,ask1))";

    for (int i = 0; i < target1.size(); ++i) {

        string alpha;
        int period;
        int begin = i;
        if (target1[i] == '(') {
            string ret = getWholeExpression("avg", target1, begin, period, alpha);

            cout << "outside begin: " << begin << endl;
            cout << "outside period: " << period << endl;
            cout << "outside alpha: " << alpha << endl;
            break;
        }
    }
    for (int i = 0; i < target2.size(); ++i) {

        string alpha;
        int period;
        int begin = i;
        double rate;
        if (target2[i] == '(') {
            string ret = getWholeExpression("ema", target2, begin, period, rate, alpha);

            cout << "outside begin: " << begin << endl;
            cout << "outside period: " << period << endl;
            cout << "outside rate: " << rate << endl;
            cout << "outside alpha: " << alpha << endl;

            exit(0);

        }
    }

    return 0;
}