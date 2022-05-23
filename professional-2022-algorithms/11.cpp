#include <iostream>
#include <unordered_map>

std::unordered_map<size_t, size_t> hash;

size_t count(size_t num) {
    if (num == 0) return 0;
    if (num < 10) return 1;

    auto v = hash.find(num);
    if (v != hash.end()) return v->second;

    size_t pow = 1;
    while (num >= pow) pow *= 10;
    pow /= 10;

    size_t left = num % pow;
    size_t digit = num / pow;

    size_t res;

    if (digit == 1) res = count(pow - 1) + left + 1;
    else res = count(pow - 1) * (digit - 1) + pow + count(left);

    hash[num] = res;
    return res;
}

int main() {
    size_t lo, hi;
    std::cin >> lo >> hi;

    std::cout << (count(hi) - count(lo - 1)) << "\n";
}