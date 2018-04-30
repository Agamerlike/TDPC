#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
typedef long long ll;
ll MOD = 1e9+7;

using namespace std;

double dp[101][101][51][51]; //i個目、2の累乗数、3の累乗数、5の累乗数

int main()
{
	int n;
	ll d;
	int d2=0;
	int d3=0;
	int d5=0;
	double ans=0;
	
	cin>>n>>d;

	//dの素因数分解
	while(d%2==0)
	{
		d2++;
		d/=2;
	}
	while(d%3==0)
	{
		d3++;
		d/=3;
	}
	while(d%5==0)
	{
		d5++;
		d/=5;
	}
	if(d!=1 || d2>100 || d3>50 || d5>50)
	{
		cout<<0<<endl;
		return 0;
	}

	//ここからDP
	fill(dp[0][0][0],dp[101][0][0],0);
	dp[0][0][0][0]=1;
	for(int i=1;i<n+1;i++)
	{
		for(int x=0;x<101;x++)
		{
			for(int y=0;y<51;y++)
			{
				for(int z=0;z<51;z++)
				{
					if(dp[i-1][x][y][z]>0)
					{
						double temp=dp[i-1][x][y][z];
						//cerr<<temp<<endl;
						dp[i][x][y][z]+=temp/6; //1
						if(x<100)
							dp[i][x+1][y][z]+=temp/6; //2
						if(x<99)
							dp[i][x+2][y][z]+=temp/6; //4
						if(y<50)
							dp[i][x][y+1][z]+=temp/6; //3
						if(x<100 && y<50)
							dp[i][x+1][y+1][z]+=temp/6; //6
						if(z<50)
							dp[i][x][y][z+1]+=temp/6; //5
					}
				}
			}
		}
	}
	//ここまでDP

	for(int x=d2;x<101;x++)
	{
		for(int y=d3;y<51;y++)
		{
			for(int z=d5;z<51;z++)
			{
				ans+=dp[n][x][y][z];
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}