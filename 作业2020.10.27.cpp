#include<stdio.h>
#include<iostream>
using namespace std;
const int N=1e4+1;
int n,m,k;
bool A[N];
void add(int &x){
	x=(x==n?1:x+1);
}
int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0;i<n;i++){
		int t=k%(n-i);
		if(!t)t=n-i;
		while(t--){
			add(m);
			while(A[m])add(m);
		}
		A[m]=1;
		printf("%d ",m);
	}
	return 0;
}
