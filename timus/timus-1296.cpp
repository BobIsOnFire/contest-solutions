#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
		    
	int k, max = 0, current = 0;
	for (int i = 0; i < N; i++) {
		cin >> k;
		current += k;
		if (current < 0) current = 0;
		if (current > max) max = current;
	}
			    
	cout << max;
}
