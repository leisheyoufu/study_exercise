// Function.h

#ifndef ALPHAPROJECT_FUNCTION_H
#define ALPHAPROJECT_FUNCTION_H

#include <string>
#include <map>
using namespace std;

namespace funcinfo {

typedef double (*pFunc) (double);
typedef double (*pFunc2Var) (double, double);

enum PFuncType {
    ONE_VAR_TYPE = 1,
    TWO_VAR_TYPE = 2,
};



double add(double value1, double value2);
double mul(double value1, double value2);
double div(double value1, double value2);
double squre(double value1);

const static map<string, pFunc2Var> func2Var = {
    {"add", add},
    {"mul", mul},
    {"div", div},
};

const static map<string, pFunc> func1Var = {
    {"square", squre},
};



const static map<string, int> funcArity = {
    {"add", 2},
    {"mul", 2},
    {"div", 2},
    {"square", 1},
};

}

#endif //ALPHAPROJECT_FUNCTION_H