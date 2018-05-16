#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;
using ll=long long;

ll dp[1001][1001]; //現在左:i番目右:j番目のとき、先手が取るスコア
// i<A+1,j<B+1

int main()
{
	int A,B;
	ll a[1001],b[1001];
	ll rui[1001];
	rui[0]=0;//左の山の上から取った累積和
	ll ss=0;
	cin>>A>>B;
	for(int i=0;i<A;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<B;i++)
	{
		cin>>b[i];
	}
	a[A]=0;
	b[B]=0;
	reverse(a,a+A+1);
	reverse(b,b+B+1);
	for(int i=1;i<A+1;i++)
		rui[i]=rui[i-1]+a[i];
	fill(dp[0],dp[1001],-1);
	dp[0][0]=0;
	//dpの更新
	for(int i=0;i<A+1;i++)
	{
		ss=rui[i];
		for(int j=0;j<B+1;j++)
		{
			ss+=b[j];
			if(i==0 && j==0)
				continue;
			else if(i==0)
				dp[i][j]=ss-dp[i][j-1];
			else if(j==0)
				dp[i][j]=ss-dp[i-1][j];
			else
				dp[i][j]=max(ss-dp[i][j-1],ss-dp[i-1][j]);
			//cerr<<ss<<endl;
		}
	}
	cout<<dp[A][B]<<endl;
	return 0;
}