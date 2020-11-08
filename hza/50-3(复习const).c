#include <stdio.h>
void printArgument(const int *);

int main()
{
  int iNum = 5;
  
  printfArgument(&iNum);
  return 0;
}

void printArgument(const int *num)
{
  printf("\n The Argument is %d", *num);
}
