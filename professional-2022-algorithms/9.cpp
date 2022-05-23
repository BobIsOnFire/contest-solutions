#include <array>
#include <iostream>
#include <string>

#define WINDOW 1
#define AISLE 2

namespace detail {
    template <typename T, std::size_t ... Is>
    constexpr std::array<T, sizeof...(Is)>
    create_array(T value, std::index_sequence<Is...>)
    {
        // cast Is to void to remove the warning: unused value
        return {{(static_cast<void>(Is), value)...}};
    }
}

template <std::size_t N, typename T>
constexpr std::array<T, N> create_array(const T& value)
{
    return detail::create_array(value, std::make_index_sequence<N>());
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string row;
    row.reserve(52);
    std::cin >> row;

    size_t len = row.length();

    auto letters = create_array<26>(0);
    letters[row[0] - 'A'] |= WINDOW;
    letters[row[len-1] - 'A'] |= WINDOW;

    for (int i = 1; i < len-1; i++) {
        if (row[i] == '.') {
            letters[row[i-1] - 'A'] |= AISLE;
            letters[row[i+1] - 'A'] |= AISLE;
        }
    }

    std::cout << "Window: ";
    for (int i = 0; i < 26; i++) {
        if (letters[i] & WINDOW) std::cout << char(i + 'A') << " ";
    }
    std::cout << "\n";

    std::cout << "Aisle: ";
    for (int i = 0; i < 26; i++) {
        if (letters[i] & AISLE) std::cout << char(i + 'A') << " ";
    }
    std::cout << "\n";
}