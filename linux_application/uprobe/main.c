#include<stdio.h>

static void
print_curr_state_one(void)
{
    printf("This is the print current state one functionn");
}


static void
print_curr_state_two(void)
{
    printf("This is the print current state two functionn");
}


int main () {
    while(1) {
        print_curr_state_one();
        sleep(1);
        print_curr_state_two();
    }
    return 0;
}