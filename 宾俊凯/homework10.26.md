```C++
#include<iostream>
int main()
{
  int n,m,k;
  cin>>n>>m>>k;
  int a[n];
  for(int i=0;i<=n-1;i++){
    a[i]=i+1;
  }
  int cul=m,ans=0;
  while(true){
    if(m==n+1){
      m=1;continue;
    }
    else if(a[m-1]==0){
      m++;continue;
    }
    else if(cul<k){
      cul++;m++;
    }
    else if(cul==k){
      cul=1;ans++;cout<<a[m-1]<<" ";
      a[m-1]=0;continue;
    }
    else if(ans==n){
      break;
    }
  }
}  
```

约瑟夫环