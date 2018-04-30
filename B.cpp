#include <iostream>

using namespace std;
using long long ll;

ll mdp[1001][1001];
ll ndp[1001][1001];
ll ss;

int main()
{
	int A,B;
	int a[1000],b[1000];
	int p[2];
	p[0]=0;
	p[1]=0;
	cin>>A>>B;
	ss=0;
	for(int i=0;i<A;i++)
	{
		cin>>a[i];
		ss+=a[i];
	}
	for(int i=0;i<B;i++)
	{
		cin>>b[i];
		ss+=b[i];
	}

	fill(mdp[0],mdp[1001],-1);
	fill(ndp[0],ndp[1001],-1);
	mdp[0][0]=0;
	ndp[0][0]=0;
	//すぬけ最後取る
	if((A+B)%2==1)
	{
		ndp[1][0]=a[A-1];
		ndp[0][1]=b[B-1];
	}else{
		//すめけ最後取る
		mdp[1][0]=a[A-1];
		mdp[0][1]=b[B-1];
	}

	return 0;
}