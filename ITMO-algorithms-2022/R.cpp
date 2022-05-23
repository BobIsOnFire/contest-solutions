#include <bits/stdc++.h>

void sort_uniq(std::vector<int> &numbers) {
    std::sort(numbers.begin(), numbers.end());

    int k = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] != numbers[k]) numbers[++k] = numbers[i];
    }
    numbers.resize(k+1);
}

struct card_slice {
    std::vector<int> cards;
    int left;
    int right;

    card_slice(std::vector<int> && nums) {
        cards = nums;
        left = 1;
        right = 1;
    }

    int cards_in_slice() {
        return right - left + 1;
    }

    int cards_span() {
        return cards[right] - cards[left] + 1;
    }

    int straight_capacity() {
        return cards[right+1] - cards[left-1] - 1;
    }

    bool valid() {
        return right >= left;
    }

    bool end_reached() {
        return right == cards.size() - 1;
    }

    void next_left() {
        left++;
    }

    void next_right() {
        right++;
    }

    int straight_count(int hand, int size) {
        // Not enough cards in hand to cover empty spaces in slice
        if (hand + cards_in_slice() < size) return 0;

        // Number of cards outside current slice, but inside possible straight 
        int outside = size - cards_span();

        // The smallest straight for this slice can start either right after the
        // previous card, or in the way that it ends on the last card in slice
        int start = std::max(cards[left-1] + 1, cards[left] - outside);

        // Same for where the biggest straight will end
        int end = std::min(cards[right+1] - 1, cards[right] + outside);

        return (end - size + 1) - start + 1;
    }
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N, M, S;
    std::cin >> N >> M >> S;

    std::vector<int> numbers(M+2, 0);

    for (int i = 0; i < M; i++) {
        std::cin >> numbers[i+1];
    }

    numbers[M+1] = N+1;
    sort_uniq(numbers);

    int count = 0;

    // Slice holds a set of consecutive cards which, with some cards from
    // player's hand, might or might not create a straight.
    card_slice slice(std::move(numbers));

    while (!slice.end_reached()) {
        // Check if there are too many cards in the slice - difference between
        // smallest and biggest card value is more than straight size. That
        // means, some of the cards will not be used in some straights, which
        // will be harder to calculate. Try to get smaller slices by advancing
        // its left bound. 
        while (slice.valid() && slice.cards_span() > M) {
            slice.next_left();
        }

        // At the moment we have the biggest slice where all cards will be used
        // in straight. Check if we can create at least one straight without
        // touching cards around the slice. 
        // Advance the right bound if no straights can be created.
        if (!slice.valid() || slice.straight_capacity() < M) {
            slice.next_right();
            continue;
        }

        // Advance left bound until there is no straight capacity left.
        while (slice.valid() && slice.straight_capacity() >= M) {            
            count += slice.straight_count(S, M);
            slice.next_left();
        }
        
        // Do not advance left bound on the last iteration, we need to check it
        // against the advanced right bound here
        slice.left--;
        slice.next_right();
    }

    std::cout << count;
}
