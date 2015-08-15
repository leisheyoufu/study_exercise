#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>


struct point {
    float x;
    float y;
};

double area2(struct point a, struct point b, struct point c)
{
    return fabs(a.x*b.y -b.x*a.y +b.x*c.y -c.x*b.y -a.x*c.y +c.x*a.y);
}

int main()
{
    struct point a, b,c;
    freopen("test.txt","r",stdin);
    while( scanf("%f %f %f %f %f %f",&a.x,&a.y,&b.x,&b.y,&c.x,&c.y) !=EOF) {
        int count = 0;
        for(int i=0; i<=99; i++) {
            for(int j=0; j<=99; j++) {

                struct point o = {i,j};
                double s= area2(o,a,b) + area2(o,b,c) +area2(o,c,a) - area2(a,b,c);
                if(s<0.0001 && s > -0.0001) {
                    count ++;
                }
            }
        }
        printf("%d\n",count);
    }
    return 0;
}
