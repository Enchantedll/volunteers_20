#include<stdio.h>
int main(){
	int n,m,k;
	scanf("%d %d %d",&n,&m,&k);
	int a[n],b[n]={0};
	for(int i=1;i<=n;i++){
		a[i-1]=i;
	}
	int s=m-1;
	for(int i=0;i<n;i++){
		s+=k;
		if(s>n)s=s-n;
		for(int j=0;j<i+1;j++){
			if(b[j]!=s)continue;
			else{
				++s;
				j=0;
				if(s<=n)continue;
				else{
					s=1;
					continue;
				}	
			}
		}
		if(s<=n){
			printf("%d ",s);
			b[i]=s;
		}
	}
	return 0;
}
