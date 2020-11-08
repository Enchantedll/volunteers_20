#include <stdio.h>

int nameLength(char []);

int main()
{
    char name[30] = {'\0'};

    printf("\nEnter your English name:");
    scanf("%s, name[]");

    printf("\nYour name contains ");
    printf("%d characters\n", nameLength(name));
    return 0;
}
//end main
int nameLength(char name[])
{
    int x =0;
    while ( name[x] != 0)
    return x;
}
//end name
