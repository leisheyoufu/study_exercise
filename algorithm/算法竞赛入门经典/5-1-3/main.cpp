#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text[1000];

int timeofword(char *word)
{
    int len = strlen(word);
    int ok;
    for(int i=1; i<len; i++)
        if( len %i ==0) {
            ok =1;
            for(int j=i; j<len; j++) {
                if(word[j] != word[j%i]) {
                    ok = 0;
                    break;
                }
            }
            if(ok)
                return i;
        }
    return 0;
}
int main()
{
    freopen("test.txt","r",stdin);
    scanf("%s",text);
    printf("%d\n", timeofword(text));
    return 0;
}
