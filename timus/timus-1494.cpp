#include <bits/stdc++.h>
#include <stack>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	unsigned int N;
	cin >> N;

	stack<int> balls;
	unsigned int time = 0, ball;
	bool cheater = false;

	for (int i = 0; i < N; i++) {
		cin >> ball;
		if (cheater) continue;

		if (ball > time) {
			for (int k = time + 1; k < ball; k++) balls.push(k);
			time = ball;
			continue;
		}
		
		if (balls.top() != ball) {
			cheater = true;
			continue;			
		}

		balls.pop();
	}

	cout << (cheater ? "Cheater" : "Not a proof") << endl;
}
