#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;

	int n, k;
	for (int i = 0; i < T; i++) {
			cin >> n >> k;
			int r = n % k;
			int d = (n - r) / k; 
			int s = d * d * k * (k - 1) / 2;
			s += r * (k - 1) * d;
			s += r * (r - 1) / 2;
			cout << s << "\n";
	}
}
