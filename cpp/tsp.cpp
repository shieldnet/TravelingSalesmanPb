#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <set>
#include <cmath>
#include <time.h>
#include <limits.h>

using namespace std;

//typedef int long long;
typedef long long LL;
typedef vector<LL> VLL;

#define MAX_NODE 24

using namespace std;

int n;
int cost[MAX_NODE][MAX_NODE];
short dp[MAX_NODE][1 << MAX_NODE];

// �湮�� ��带 �����ϰ� ���� node���� �������� ��ȸ�ϴ� ���
int tsp(int here, int visited) {
	if (visited == ((1 << n) - 1)) { // ���� �湮�� ���
		if (cost[here][1] != 0)
			return cost[here][1];
	}

	short &ret = dp[here][visited];
	if (ret != 0) return ret;
	ret = 20000000;

	for (int i = 1; i <= n; i++) {
		if (!(visited & (1 << (i - 1))) && cost[here][i] != 0) { // i �� ��尡 �湮���� �ʾҴٸ�
			ret = min((int)ret, cost[here][i] + tsp(i, visited | (1 << (i - 1))));
			// i �� ��� �湮üũ�ϰ� i�� ���������� ���
		}
	}

	return ret;
}

int main() {
	int n =1;
	FILE* result = NULL;
	result = fopen("result.txt", "w");

	for(int i = 0; i<23; i++){
		memset(cost, 0, sizeof(cost));
		memset(dp, 0, sizeof(dp));
		n++;
		if(n==MAX_NODE+1) break;
		FILE* fp = NULL;
		char file_name[100];

		sprintf(file_name,"%d",n);

		strcat(file_name, ".txt");

		fp = fopen(file_name, "r");

		fscanf(fp,"%d ", &n);

		clock_t st = clock();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				fscanf(fp," %d", &cost[i][j]);


		int ans = tsp(1, 1);
		clock_t fin = clock();

		printf("Minimum Cost When N=%d :: %d. Execution time : %d ms\n", n, ans, fin-st );
		fprintf(result, "Minimum Cost When N=%d :: %d. Execution time : %d ms\n", n, ans, fin - st);

		fclose(fp);
	}
	fclose(result);
	return 0;
}
