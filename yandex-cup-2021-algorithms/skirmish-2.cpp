/*

Нужно определить, можно ли из исходной последовательности получить конечную,
используя следующие преобразования:
1. Перемешать числа в последовательности
2. Прибавить ко всем числам одно и то же число
3. Умножить все числа на одно и то же ненулевое число

На вход поступают:

Первая строка - количество тестов T.
Далее, для каждого теста:
  Первая строка - количество чисел N в исходной последовательности
  Вторая строка - N чисел - исходная последовательность
  Третья строка - количество чисел M в конечной последовательности
  Четвертая строка - M чисел - конечная последовательность

На выход, для каждого теста, нужно вывести YES, если можно получить конечную,
или NO, если нельзя.

*/

#include <algorithm>
#include <iostream>
#include <vector>

bool process_forward(std::vector<int> &x, std::vector<int> &y, int N) {
	long a = ((long) y[N - 1]) - y[0];
	long b = ((long) x[N - 1]) * y[0] - ((long) x[0]) * y[N - 1];
	long c = ((long) x[N - 1]) - x[0];

	if (a == 0 && c != 0) return false;

	for (int i = 1; i < N - 1; i++) {
		if (a * x[i] + b != c * y[i]) return false;
	}

	return true;
}

bool process_backward(std::vector<int> &x, std::vector<int> &y, int N) {
	long a = ((long) y[0]) - y[N - 1];
	long b = ((long) x[N - 1]) * y[N - 1] - ((long) x[0]) * y[0];
	long c = ((long) x[N - 1]) - x[0];

	if (a == 0 && c != 0) return false;

	for (int i = 1; i < N - 1; i++) {
		if (a * x[i] + b != c * y[N - 1 - i]) return false;
	}

	return true;
}

bool process_test() {
	int N;
	std::cin >> N;
	std::vector<int> x(N);

	for (int i = 0; i < N; i++) {
		std::cin >> x[i];
	}
	std::sort(x.begin(), x.end());

	int M;
	std::cin >> M;
	std::vector<int> y(M);

	for (int i = 0; i < M; i++) {
		std::cin >> y[i];
	}
	std::sort(y.begin(), y.end());

	if (N != M) return false;
	if (N < 2) return true;

	return process_forward(x, y, N) || process_backward(x, y, N);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int tests;
	std::cin >> tests;

	for (int t = 0; t < tests; t++) {
		std::cout << (process_test() ? "YES\n" : "NO\n");
	}
}
