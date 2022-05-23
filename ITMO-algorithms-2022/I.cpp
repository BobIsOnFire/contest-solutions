#include <bits/stdc++.h>
#include <queue>

struct car {
    int num;
    int next;
};

// location - index of each element in the heap (-1 if no such element in the heap)
struct queue {
private:
    std::vector<int> location;
    std::vector<car> heap;
    int capacity;

    std::size_t parent(std::size_t i) {
        return (i - 1) / 2;
    }

    std::size_t left(std::size_t i) {
        return 2 * i + 1;
    }

    std::size_t right(std::size_t i) {
        return 2 * i + 2;
    }

    void heap_swap(std::size_t i, std::size_t j) {
        std::swap(location[heap[i].num], location[heap[j].num]);
        std::swap(heap[i], heap[j]);
    }

    void siftup(std::size_t i) {
        while (i > 0 && heap[parent(i)].next < heap[i].next) {
            heap_swap(i, parent(i));
            i = parent(i);
        }
    }

    void siftdown(std::size_t i) {
        std::size_t j = i;
        std::size_t n = heap.size();
        while (true) {
            if (left(i) < n && heap[j].next < heap[left(i)].next) {
                j = left(i);
            }
            if (right(i) < n && heap[j].next < heap[right(i)].next) {
                j = right(i);
            }
            if (i == j) break;
            heap_swap(i, j);
            i = j;
        }
    }

public:

    queue(int N, int K) {
        location = std::vector<int> (N, -1);
        heap.reserve(K);
        capacity = K;
    }

    // true if we either add or replace existing car
    bool push(car x) {
        if (location[x.num] >= 0) {
            // if car is already in, do not push anything, increase existing key
            heap[location[x.num]] = x;

            siftup(location[x.num]);
            return false;
        }

        // insert new car
        if (heap.size() < capacity) {
            heap.push_back(x);
            location[x.num] = heap.size() - 1;

            siftup(heap.size() - 1);
            return true;
        }

        // replace existing car
        location[heap.front().num] = -1;
        heap.front() = x;
        location[x.num] = 0;

        siftdown(0);
        return true;
    }

    void print() {
        std::cout << "Heap locations:\n";
        for (int i = 0; i < location.size(); i++) {
            if (location[i] == -1) continue;
            std::cout << (i+1) << ": " << location[i] << "\n";
        }
        std::cout << "Heap itself:\n";
        for (auto c : heap) {
            std::cout << "(" << (c.num+1) << " " << c.next << ") ";
        }
        std::cout << "\n";
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, K, P;
    std::cin >> N >> K >> P;

    std::vector<int> last_idx(N, -1);
    std::vector<car> ops(P, car{});
    
    for (int i = 0; i < P; i++) {
        int a;
        std::cin >> a;
        a--;

        ops[i] = {a, P};
        
        if (last_idx[a] >= 0) {
            ops[last_idx[a]].next = i;
        }
        last_idx[a] = i;
    }

    queue q(N, K);
    int count = 0;

    for (auto c : ops) {
        if (q.push(c)) count++;
        // q.print();
    }

    std::cout << count;
}
