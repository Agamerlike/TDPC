#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
typedef long long ll;
ll MOD = 1e9+7;

using namespace std;

double r[1050];
double ratio[1050][1050]; //iがjに勝つ確率
double dp[1050][11];//iがj回戦まで勝ち残る確率

int main()
{
	int k;
	int n;
	int ans=0;
	
	cin>>k;
	n=pow(2,k);
	for(int i=0;i<n;i++)
	{
		cin>>r[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j)
				continue;
			ratio[i][j]=(double)1/(double)(1+pow(10,(r[j]-r[i])/400));
		}
	}

	//ここからdp
	fill(dp[0],dp[1050],0);
	//初期値
	for(int i=0;i<n;i++)
	{
		if(i%2==0)
			dp[i][0]=ratio[i][i+1];
		else
			dp[i][0]=ratio[i][i-1];
	}
	for(int j=1;j<k;j++)
	{
		int num=pow(2,j+1);//1組あたりの数
		int half=num/2;
		int group=n/num;
		for(int k=0;k<group;k++)
		{
			//グループ内はじめのhalf組について調べる		
			for(int i=0;i<half;i++)
			{
				for(int m=half;m<num;m++)
				{
					dp[k*num+i][j]+=ratio[k*num+i][k*num+m]*dp[k*num+i][j-1]*dp[k*num+m][j-1];
				}
			}
			//あとのhalf組
			for(int i=half;i<num;i++)
			{
				for(int m=0;m<half;m++)
				{
					dp[k*num+i][j]+=ratio[k*num+i][k*num+m]*dp[k*num+i][j-1]*dp[k*num+m][j-1];
				}
			}
		}
	}
	//dpここまで

	for(int i=0;i<n;i++)
	{
		cout<<fixed<<dp[i][k-1]<<endl;
	}
	return 0;
}