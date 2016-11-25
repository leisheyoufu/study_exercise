#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<algorithm>

const char SEP[] = {' ', ',','.'};
char temp2[80];
struct Source {
    char *content;
    int size;
    int pos;

    Source(char *str) {
        this->content = str;
        this->size = strlen(str);
        pos = 0;
    }

    bool in(char c) {
        int i=0;
        int len = sizeof(SEP);
        while(i<len) {
            if(SEP[i++] == c) {
                return true;
            }
        }
        return false;
    }

    char *next1() {
        int i=0;
        while(i==0 && pos!=size) {
            while( !in(content[pos+i])) {
                i++;
            }
            if(i==0) {
                pos++;
            }
        }
        if(pos == size) {
            return NULL;
        }
        char *temp = (char*)malloc(i+1);
        strncpy(temp,content+pos,i);
        temp[i] = '\0';
        pos+=i;
        return temp;
    }

    char *next2() {
        int i=0;
        while(pos!=size) {
            if (!in(content[pos])) {
                temp2[i++] = content[pos++];
            } else if(i!=0) {
                temp2[i] = '\0';
                return temp2;
            } else {
                pos++;
            }
        }
        return NULL;
    }
};

int main()
{
    char *str="hello, this is xianglin speaking.";
    Source * s = new Source(str);
    char * temp;
    while( (temp = s->next1()) != NULL) {
        printf("%s\n",temp);
        free(temp);
    }
    delete s;
    printf("\ncase 2\n\n");
    s = new Source(str);
    while( (temp = s->next2()) != NULL) {
        printf("%s\n",temp);
    }

    getch();
    return 0;
}
