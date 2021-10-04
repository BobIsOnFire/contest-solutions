/*

Дан набор плиток 2×2. У каждой плитки четыре квадрата покрашены в один из трех
цветов: белый (W), черный (B) или красный (R).

Определите, можно ли из набора плиток составить пиксельную картину N×M (стороны
картины имеют четный размер), если плитки при выкладывании не должны
перекрываться и не могут выходить за пределы картины. При выкладывании плитки
можно поворачивать, но нельзя ломать.

Плитка непрозрачная, и краска нанесена только с одной стороны плитки.

В первой строке дано число k (1 ≤ k ≤ 10^5) — количество плиток в наборе.
В следующих 2k строках даны описания плиток. Описание каждой плитки занимает две
строки по два символа, они задают цвета квадратов плитки. Далее даны два числа 
n и m (2 ≤ n,m ≤ 512, n и m четные) — размеры картины. В каждой из следующих n
строк дано описание очередного ряда картины. При описании плиток и пикселей
картины используются только символы W, B и R.

В единственной строке выведите Yes, если из набора плиток можно собрать картину,
иначе выведите No.
--------------------------------------------------------------------------------
Примеры:

ВВОД
1
WW
BW
2 2
WB
WW

ВЫВОД
Yes
---------------------------------------
ВВОД
3
WW
WW
WW
WW
BB
BB
4 2
WW
BB
BB
WW

ВЫВОД
No
---------------------------------------
ВВОД
4
RR
RR
WW
WW
BB
BB
WW
WW
4 4
WWBB
WWBB
RRWW
RRWW

ВЫВОД
Yes
--------------------------------------------------------------------------------
*/

#include <iostream>

int ror(int x, int rot) {
    return ((x >> 2*rot) | (x << 2*(4-rot))) & 0xFF;
}

int find_tile(int tile) {
    return std::min(
        std::min(tile, ror(tile, 1)),
        std::min(ror(tile, 2), ror(tile, 3))
    );
}

int from_char(char c) {
    if (c == 'W') return 0;
    if (c == 'B') return 1;
    return 2;
}

int get_hash(char c1, char c2, char c3, char c4) {
    int collect = (from_char(c1) << 6) | (from_char(c2) << 4) | (from_char(c3) << 2) | from_char(c4);
    return find_tile(collect);
}

int main() {
    int k;
    std::cin >> k;

    int tiles[256] = {0};

    for (int i = 0; i < k; i++) {
        std::string first, second;
        std::cin >> first >> second;
        tiles[get_hash(first[0], first[1], second[1], second[0])]++;
    }

    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n/2; i++) {
        std::string first, second;
        std::cin >> first >> second;
        for (int j = 0; j < m; j += 2) {
            int hash = get_hash(first[j], first[j+1], second[j+1], second[j]);
            if (tiles[hash] == 0) {
                std::cout << "No\n";
                return 0;
            }
            tiles[hash]--;
        }
    }

    std::cout << "Yes\n";
    return 0;
}
