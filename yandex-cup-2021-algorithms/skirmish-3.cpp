/*

Строка d_26 составляется по следующему рекуррентному правилу:
- d_1 = a
- d_2 = aba
- d_i = d_(i-1) + alphabet[i] + d_(i-1),
где alphabet[i] - i-ая строчная буква латинского алфавита.

На вход поступает строка S из заглавных букв латинского алфавита, каждая из
которых соответствует некоторой строчной букве (необязательно A соответствует a)

Нужно определить, есть ли такое соответствие заглавных и строчных букв, что S
является подстрокой d_26. Если соответствия нет, вывести "No solution". Если
соответствие есть, вывести:

В первой строке - соответствие заглавных букв из строки S слову abcdefg...xyz;
Во второй строке - минимальный номер, начиная с которого в d_26 можно найти
слово S (первая буква под номером 1).

*/

#include <iostream>

char test_char(std::string &s, int start, int step) {
	char ch = s[start];
	for (int i = start; i < s.length(); i += step) {
		if (s[i] != ch) return 0;
	}
	return ch;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s;
	std::cin >> s;

	char map[26];
	int revmap[26];
	for (int i = 0; i < 26; i++) revmap[i] = -1;

	int start = 0, step = 2, idx = 0;

	while (start < s.length()) {
		char res = test_char(s, start, step);
		if (res && revmap[res - 'A'] < 0) {
			map[idx++] = res;
			revmap[res - 'A'] = start;
			start += step / 2;
 			step *= 2;
			continue;
		} else {
			res = test_char(s, start + step / 2, step);
			if (res && revmap[res - 'A'] < 0) {
				map[idx++] = res;
				revmap[res - 'A'] = start + step / 2;
				step *= 2;
				continue;
			} else {
				std::cout << "No solution\n";
				return 0;
			}
		}
	}

	for (int i = 0; i < idx; i++) {
		std::cout << map[i];
	}
	for (int i = 0; i < 26; i++) {
		if (revmap[i] < 0) std::cout << char('A' + i);
	}
	std::cout << '\n';

	int pow = 1;
	for (int i = 1; i < idx; i++) {
		pow *= 2;
		if (revmap[map[i] - 'A'] < revmap[map[i - 1] - 'A']) {
			std::cout << (pow - revmap[map[i] - 'A']) << "\n";
			return 0;
		}
	}

	std::cout << "1\n";
	return 0;
}
