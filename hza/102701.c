#include<stdio.h>

int n, m, k, j;//global variable
int main()
{
    printf("Enter n, m, k\n");
    scanf("%d%d%d",&n, &m, &k );
    int num[n];

    for(int i=0;i<n;i++)//简化
        num[i] = i+1;

    if(m+k-1<n)
        j = m+k-1;
    else if((m+k-1)%n!=0)
        j = (m+k-1)%n;
    else j = n;

    for(int i = 1;i<=n;i++){
        printf("%d\n",num[j-1]);
        num[j-1] = 0;
        for(int x = 0;x<k;){
            if(j<n)
                j++;
            else
                j = 1;
            if(num[j-1]!=0)
                x++;
            else
                x = x;
        }
    }
    return 0;
}
