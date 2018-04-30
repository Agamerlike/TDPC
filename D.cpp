#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
typedef long long ll;
ll MOD = 1e9+7;

using namespace std;

ll dp[9999999];

int main()
{
	int n;
	ll d;
	double ans;
	
	cin>>n>>d;
	fill(dp,dp+9999999,0);
	for(int i=1;i<7;i++)
	{
		dp[i]=1;
	}
	for(int i=1;i<n;i++)
	{
		for(int j=pow(6,i);j>-1;j--)
		{
			if(dp[j]>0)
			{
				for(int m=2;m<7;m++)
				{
					dp[j*m]+=dp[j];
				}
			}
		}
	}

	if(d>pow(6,n))
	{
		ans=0;
	}else{
		ll cnt=0;
		for(int i=d;i<pow(6,n)+1;i+=d)
		{
			cnt+=dp[i];
		}
		ans=(double)cnt/(double)pow(6,n);
	}
	cout<<ans<<endl;
	return 0;
}