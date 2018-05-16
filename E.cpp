#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
typedef long long ll;
ll MOD = 1000000007;

using namespace std;

ll dp[10001][100];
int nn[10000];

int main()
{
	string n;
	int d;
	ll ans=0;
	int keta;
	
	cin>>d;
	cin>>n;
	keta = n.length();
	for(int i=0;i<keta;i++)
	{
		nn[i]=(n[i]-'0');
	}
	fill(dp[0],dp[10001],0);

	//DP初期値設定（1桁目）
	for(int i=0;i<10;i++)
	{
		int f = i%d;
		dp[1][f]++;
	}

	//ここからDP
	for(int i=2;i<keta;i++)
	{
		for(int j=0;j<d;j++)
		{
			if(dp[i-1][j]>0)
			{
				for(int k=0;k<10;k++)
				{
					int f = (j+k)%d;
					dp[i][f]++;
					dp[i][f]%=MOD;
				}
			}
		}
	}
	/*
	//最後の桁の最大数-1まで調べる
	for(int j=0;j<d;j++)
	{
		if(dp[keta-1][j]>0)
		{
			for(int k=0;k<nn[0];k++)
			{
				int f = (j+k)%d;
				dp[keta][f]++;
				dp[keta][f]%=MOD;
			}
		}
	}
	*/
	for(int i=1;i<keta;i++)
	{
		for(int j=0;j<d;j++)
		{
			cerr<<dp[i][j]<<" ";
		}
		cerr<<endl;
	}
	ans=dp[keta-1][0];
	cout<<ans<<endl;
	return 0;
}