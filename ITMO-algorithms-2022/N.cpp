#include <bits/stdc++.h>

struct pig {
    int location;
    bool visited = false;
    int group = -1;
} pigs[100];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        std::cin >> pigs[i].location;
        pigs[i].location--;
    }

    int group_count = 0;
    for (int i = 0; i < N; i++) {
        
        int k = i;
        while (!pigs[k].visited && pigs[k].group == -1) {
            pigs[k].visited = true;
            k = pigs[k].location;
        }

        int cur_group = pigs[k].group;

        if (cur_group == -1) {
            cur_group = ++group_count;
        }

        k = i;
        while (pigs[k].group == -1) {
            pigs[k].group = cur_group;
            k = pigs[k].location;
        }
    }

    std::cout << group_count;
}