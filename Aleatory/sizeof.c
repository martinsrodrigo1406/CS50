#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *c[] = {"dfg", "cd", "de", "ef"};
    
    
    printf("%lu\n", sizeof(c) / sizeof(char*));
}