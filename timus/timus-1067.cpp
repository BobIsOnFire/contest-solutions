#include <bits/stdc++.h>
#include <map>
#include <string>
#include <sstream>
using namespace std;

struct directory {
	map<string, directory*> children;
};

void print(directory* dir, int depth) {
	for (auto s : dir->children) {
		for (int i = 0; i < depth; i++) cout << ' ';
		cout << s.first << '\n';
		print(s.second, depth + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	directory* root = new directory;
	for (int i = 0; i < N; i++) {
		string line, dir;
		cin >> line;

		stringstream ss(line);
		directory* current = root;
		while(getline(ss, dir, '\\')) {
			auto& el = current->children[dir];
			if (el) {
				current = el;
			} else {
				directory* t = new directory;
				current->children[dir] = t;
				current = t;
			}
		}
	}

	print(root, 0);
}
