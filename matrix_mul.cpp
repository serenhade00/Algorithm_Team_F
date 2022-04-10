#include <bits/stdc++.h>

using namespace std;

int mul[501][501]; // 행렬끼리 곱 연산 횟수 저장. ex) mul[1][4] = 1번째와 4번째 행렬의 곱 연산 횟수 저장
int mat[501][2]; // 행렬의 행,열을 각각 저장. ex) mat[1][1] = 1번째 행렬의 행, mat[1][2] = 1번째 행렬의 열

const int INF = 0x7ffffff; // 최소 횟수 갱신을 위해 최초 비교값을 int 형의 최댓값으로 설정

int main(void)
{
	ios::sync_with_stdio(0); // 입출력 시간 개선
	cin.tie(0);              // 입출력 시간 개선
	
	int n;                   // 행렬 개수
	cin >> n;
	
	for(int i=1; i<=n; i++)
		cin >> mat[i][0] >> mat[i][1];   // 각 행렬의 행과 열을 입력 받음
	
	for(int t=1; t<n; t++)               // 부분문제 크기 조절 위한 변수
	{
		for(int i=1; i<=n-t; i++)        // t의 크기에 따라 곱할 첫번째 행렬 범위 조정 
		{
			int j = i+t;                 // t의 크기에 따라 곱할 두번째 행렬 범위 조절 
			mul[i][j] = INF;             // 연산 값 갱신을 위해 최초 값을 int형의 최댓값 설정
			for(int k=i; k<j; k++)       // 두 행렬을 곱할때, 중간 지점 설정, 즉 부분문제 범위 설정
			{
				int tmp = mul[i][k]+mul[k+1][j]+(mat[i][0]*mat[k][1]*mat[j][1]); // 왼쪽 부분 문제+오른쪽 부분 문제+현재 곱셈 연산값 
				mul[i][j] = min(mul[i][j], tmp); // 만약 tmp값이 이미 저장된 연산값보다 작다면 갱신
			}
		}
	}
	
	cout << mul[1][n]; // 첫번째부터 n번째 행렬까지 계산한 최소 연산 결과 출력
}