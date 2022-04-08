#include <bits/stdc++.h>

using namespace std;

int mul[501][501];
int mat[501][2];

const int INF = 0x7ffffff;

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for(int i=1; i<=n; i++)
		cin >> mat[i][0] >> mat[i][1];
	
	for(int t=1; t<n; t++)
	{
		for(int i=1; i<=n-t; i++)
		{
			int j = i+t;
			mul[i][j] = INF;
			for(int k=i; k<j; k++)
			{
				int tmp = mul[i][k]+mul[k+1][j]+(mat[i][0]*mat[k][1]*mat[j][1]);
				mul[i][j] = min(mul[i][j], tmp);
			}
		}
	}
	
	cout << mul[1][n];
}