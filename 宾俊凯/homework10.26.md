```C++
#include<iostream>
#include<cstring>
using namespace std;
int a[10000];
int main(){
	memset(a,1,sizeof(a));
	int n=0,m=0,k=0;
	cin>>n>>m>>k;int i=m,cul=1,ans=0;
	while(true){
		if(a[i]==0){
			i++;continue;
		}
		else if(i==n+1)i=1; 
		else if(cul<k){
			i++;cul++;continue;
		}
		else if(cul==k){
			a[i]=0;cout<<i<<' ';cul=1;ans++;continue;
		}
		else if(ans==n)break;
	}
}
```

约瑟夫环