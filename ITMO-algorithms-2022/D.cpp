#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int start, multiplier, experiment, capacity;
    size_t days_total;

    std::cin >> start >> multiplier >> experiment >> capacity >> days_total;

    // Reproduction and experimenting are balanced
    if (multiplier * start - experiment == start) {
        std::cout << start;
        return 0;
    }

    // Bacteria amount is either always decreasing or always increasing
    // Should not take more than 1000 iterations
    size_t days = 0;

    while (start > 0 && (days == 0 || start < capacity)) {
        days++;

        // Reproduction
        start *= multiplier;
        // Experiment
        start = std::max(start - experiment, 0);
        // Storage
        start = std::min(start, capacity);

        if (days == days_total) {
            std::cout << start;
            return 0;
        }
    }

    // Bacteria amount either:
    // * Was decreasing and reached 0 - experiment ended before K days
    // * Was increasing and reached capacity - capacity will be reached each time
    std::cout << start;
    return 0;
}
