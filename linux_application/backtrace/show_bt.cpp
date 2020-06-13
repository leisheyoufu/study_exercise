/* show_bt.cpp */
#include <execinfo.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*-----------------------------------------------------------------------------------*/
/*
 * Parse a string which was returned from backtrace_symbols() to get the symbol name
 * and the offset.
 */

void parseStrings(char * stackFrameString, char * symbolString, char * offsetString)
{
    char *        symbolStart = NULL;
    char *        offsetStart = NULL;
    char *        offsetEnd = NULL;
    unsigned char stringIterator = 0;

    //iterate over the string and search for special characters
    for(char * iteratorPointer = stackFrameString; *iteratorPointer; iteratorPointer++) {
        //The '(' char indicates the beginning of the symbol
        if(*iteratorPointer == '(') {
            symbolStart = iteratorPointer;
        }
        //The '+' char indicates the beginning of the offset
        else if(*iteratorPointer == '+') {
            offsetStart = iteratorPointer;
        }
        //The ')' char indicates the end of the offset
        else if(*iteratorPointer == ')') {
            offsetEnd = iteratorPointer;
        }

    }
    //Copy the symbol string into an array pointed by symbolString
    for(char * symbolPointer = symbolStart+1; symbolPointer != offsetStart; symbolPointer++) {
        symbolString[stringIterator] = *symbolPointer;
        ++stringIterator;
    }
    //Reset string iterator for the new array which will be filled
    stringIterator = 0;
    //Copy the offset string into an array pointed by offsetString
    for(char * offsetPointer = offsetStart+1; offsetPointer != offsetEnd; offsetPointer++) {
        offsetString[stringIterator] = *offsetPointer;
        ++stringIterator;
    }
}


class MyException
{
public:
    MyException();
    virtual ~MyException();
    virtual string show_backtrace() const;
protected:
    static const int BT_SIZE=64;
    void * bt_info[BT_SIZE];
    int bt_size;
    char **    stackFrameStrings;
};

MyException::MyException():bt_size(0)
{
    bt_size = backtrace(bt_info, BT_SIZE);
    stackFrameStrings = backtrace_symbols(bt_info, (int)bt_size);
}

MyException::~MyException() {}

string MyException::show_backtrace() const
{
    string bt_string;
    ostringstream oss;
    for (int i = 0; i < bt_size; ++i) {
        char       symbolString[75] = {'\0'};
        char       offsetString[25] = {'\0'};
        cout << stackFrameStrings[i] << endl;
        parseStrings(stackFrameStrings[i], symbolString, offsetString);
        //oss << bt_info[i] <<" ";
        oss << offsetString << " ";
    }
    bt_string = oss.str();
    return bt_string;
}

void function1();
void function2();
void function3();

void function1()
{
    function2();
}
void function2()
{
    function3();
}
void function3()
{
    throw MyException();
}

int main(int argc, char * argv[])
{
    try {
        function1();
    } catch (const MyException &e) {
        cout << e.show_backtrace() <<endl;
    }

    return 0;
}
