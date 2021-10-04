/*

Сравните два числа в двоичной системе счисления. Числа представлены
последовательностью слов без пробелов, обозначающих цифры (0 — zero, 1 — one).

Выведите символ > (ASCII 62), если первое число больше второго, символ < (ASCII
60), если второе число больше первого, иначе выведите символ = (ASCII 61).
--------------------------------------------------------------------------------
Примеры:

ВВОД
oneone
onezerozero

ВЫВОД
<
---------------------------------------
ВВОД
zero
zero

ВЫВОД
=
---------------------------------------
ВВОД
oneonezerozero
onezeroonezero

ВЫВОД
>
--------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <cmath>

#define print_exit(msg) { std::cout << (msg); return 0; }

int main() {
    std::string num1, num2;
    std::cin >> num1 >> num2;

    char * iter1 = &num1[0];
    char * iter2 = &num2[0];

    int len1 = 0, len2 = 0;
    bool equal = true, greater = false;
    while (*iter1 || *iter2) {
        bool one1 = false, one2 = false;
        if (*iter1) {
            one1 = *iter1 == 'o';
            iter1 += one1 ? 3 : 4;
            len1++;
        }
        
        if (*iter2) {
            one2 = *iter2 == 'o';
            iter2 += one2 ? 3 : 4;
            len2++;
        }

        if (equal) {
            equal = one1 == one2;
            greater = one1 && !one2;
        }
    }

    if (len1 > len2) print_exit(">");
    if (len1 < len2) print_exit("<");
    if (greater) print_exit(">");
    if (equal) print_exit("=");
    print_exit("<");    
}
