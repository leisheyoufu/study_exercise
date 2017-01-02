#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

int f[100001];

void get_fail(char *needle)
{
    int len = strlen(needle);
    f[0] = 0, f[1] = 0;
    for(int i =1; i<len; i++) {
        int j = f[i];
        while(j&& needle[j] != needle[i]) {
            j = f[j];
        }
        f[i+1] = needle[j] == needle[i]? j+1:0;
    }
}

int strStr(char* haystack, char* needle)
{
    int len = strlen(haystack);
    int m = strlen(needle);
    if (m==0)
        return 0;
    get_fail(needle );
    int j =0;
    for(int i=0; i<len; i++) {
        while(j&& haystack[i] != needle[j]) {
            j = f[j];
        }
        j = haystack[i] == needle[j]? j+1:0;
        if (j == m) {
            return i-m+1;
        }
    }
    return -1;
}
int main()
{
    printf("%d\n", strStr("eabc","cbc"));
    system("pause");

    return 0;
}
