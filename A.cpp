#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	int p[100];
	bool dp[10001];
	int dp_max=0;
	int cnt=0;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>p[i];
	}
	//sort(p,p+n); //ソートはDPにおいて際立って計算量を少なくするわけではないので不要
	for(int i=0;i<n;i++)
	{
		cerr<<p[i]<<endl;
	}
	for(int i=0;i<10001;i++)
	{
		dp[i]=false;
	}
	//ここからDP
	/*
	for(int j=0;j<dp_max+1;j++)
	{
		if()
	}
	のようにした場合不可。正しい出力をしない入力例としては、"1 6 1"など。
	1回のDPループ内で更新された場所が再度更新されることが起こりうるため。
	*/
	dp[0]=true;
	for(int i=0;i<n;i++)
	{
		for(int j=dp_max;j>=0;j--)
		{
			if(dp[j]==true)
			{
				dp[j+p[i]]=true;
			}
		}
		dp_max+=p[i];
	}
	//ここまでDP
	for(int i=0;i<dp_max+1;i++)
	{
		if(dp[i]==true)
		{
			cerr<<i<<endl;
			cnt++;
		}
	}
	cout<<cnt<<endl;
	return 0;
}