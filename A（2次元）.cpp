#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	int p[100];
	bool dp[101][10001];
	int dp_max=0;
	int cnt=0;
	cin>>n;
	for(int i=1;i<n+1;i++)
	{
		cin>>p[i];
	}
	for(int i=1;i<n+1;i++)
	{
		cerr<<p[i]<<endl;
	}
	for(int i=0;i<101;i++)
	{
		for(int j=0;j<10001;j++)
		{
			dp[i][j]=false;
		}
	}
	//ここからDP
	dp[0][0]=true;
	for(int i=1;i<n+1;i++)
	{
		for(int j=0;j<dp_max+1;j++)
		{
			if(dp[i-1][j]==true)
			{
				dp[i][j]=true;
				dp[i][j+p[i]]=true;
			}
		}
		dp_max+=p[i];
	}
	//ここまでDP
	for(int i=0;i<dp_max+1;i++)
	{
		if(dp[n][i]==true)
		{
			cerr<<i<<endl;
			cnt++;
		}
	}
	cout<<cnt<<endl;
	return 0;
}