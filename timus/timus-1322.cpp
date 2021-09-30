#include <iostream>
using namespace std;

int main() {
	int K;
	cin >> K;
	char inp[100001];
	cin >> inp;
	
	long len;
	while (inp[len] > 0) len++;
 
	long unique[128];
	long freq[len];
	for (int i = 0; i < len; i++) {
		freq[i] = unique[inp[i]];
		unique[inp[i]]++;
	}


	long sum = 0;
	for (int i = 0; i < 128; i++) {
		long t = unique[i];
		unique[i] = sum;
		sum += t;
	}
	
	K--;
	char result[len + 1];
	result[len] = 0;
	result[len - 1] = inp[K];
	
	for (int i = len - 2; i >= 0; i--) {
		K = freq[K] + unique[inp[K]];
		result[i] = inp[K];
	}

	cout << result << endl;
}
