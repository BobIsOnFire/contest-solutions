#include <bits/stdc++.h>
#include <math.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int red[4];
	int blue[4];

	int s1 = 0, s2 = 0;
	
	cin >> red[0] >> blue[0] >> red[1] >> blue[1];
	cin >> blue[2] >> red[2] >> blue[3] >> red[3];

	for (int i = 0; i < 4; i++) {
		s1 += red[i];
		s2 += blue[i];
	}

	if (s1 != s2) {
		cout << "IMPOSSIBLE\n";
		return 0;
	}

	int map[4][3] = {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}};
	char rednames[4] = {'A', 'C', 'F', 'H'};
	char bluenames[4] = {'B', 'D', 'E', 'G'};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			int index = map[i][j];
			int n = min(red[i], blue[index]);

			red[i] -= n;
			blue[index] -= n;
			s1 -= n;

			for (int k = 0; k < n; k++) {
				cout << rednames[i] << bluenames[index] << '-' << endl;
			}
		}
	}

	if (s1 == 0) return 0;

	string prints[4] = {"DH+\nAD-\nGH-", "DH+\nCD-\nEH-", "AE+\nEF-\nAD-", "AE+\nEH-\nAB-"};

	for (int i = 0; i < 4; i++) {
		if (red[i] == 0) continue;
		for (int k = 0; k < red[i]; k++) cout << prints[i] << endl;
	}
}
