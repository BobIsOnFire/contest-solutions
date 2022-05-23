#include <bits/stdc++.h>
#include <cstddef>

template<typename T>
class ArrayPtr {
    int idx;

public:
    static T objects[100001];
    static ArrayPtr<T> Nil;

    ArrayPtr() : idx(-1) {}
    ArrayPtr(int i) : idx(i) {}
    ArrayPtr(T obj) : idx(0) { objects[0] = obj; }

    operator int() { return idx; }
    ArrayPtr<T> operator++(int) {
        return idx++;
    }

    T* operator->() const { return &objects[idx]; }
    T& operator*() { return objects[idx]; }

    bool nil() {
        return idx == -1;
    }

    friend bool operator<(ArrayPtr<T> self, ArrayPtr<T> other) {
        return objects[self.idx] < objects[other.idx];
    }

    friend bool operator==(ArrayPtr<T> self, ArrayPtr<T> other) {
        return objects[self.idx] == objects[other.idx];
    }
};

struct Block {
    int size;
    int start = 0;
    ArrayPtr<Block> prev = ArrayPtr<Block>::Nil;
    ArrayPtr<Block> next = ArrayPtr<Block>::Nil;
    bool taken = false;

    bool operator<(const Block & other) const {
        if (size == other.size) return start < other.start;
        return size < other.size;
    }

    bool operator==(const Block & other) const {
        return start == other.start && size == other.size;
    }
};

ArrayPtr<Block> back = 1;

template<typename T> T ArrayPtr<T>::objects[100001] = {};
template<typename T> ArrayPtr<T> ArrayPtr<T>::Nil = -1;

template<>
struct std::hash<ArrayPtr<Block>> {
    std::size_t operator()(ArrayPtr<Block> x) const {
        return (std::size_t(x->start) << 32) + x->size;
    }
};

class Heap {
private:
    std::vector<const ArrayPtr<Block>*> m_heap;
    std::unordered_map<ArrayPtr<Block>, std::size_t> m_location;

    std::size_t parent(std::size_t i) { return (i - 1) / 2; }
    std::size_t left(std::size_t i) { return 2 * i + 1; }
    std::size_t right(std::size_t i) { return 2 * i + 2; }

    void heap_swap(std::size_t i, std::size_t j) {
        std::swap(m_heap[i], m_heap[j]);
        m_location[*m_heap[i]] = i;
        m_location[*m_heap[j]] = j;
    }

    void siftup(std::size_t i) {
        if (i >= m_heap.size()) return;
        while (i > 0 && *m_heap[parent(i)] < *m_heap[i]) {
            heap_swap(i, parent(i));
            i = parent(i);
        }
    }

    void siftdown(std::size_t i) {
        if (i < 0) return;
        std::size_t j = i;
        std::size_t n = m_heap.size();
        while (true) {
            if (left(i) < n && *m_heap[j] < *m_heap[left(i)]) {
                j = left(i);
            }
            if (right(i) < n && *m_heap[j] < *m_heap[right(i)]) {
                j = right(i);
            }
            if (i == j) break;
            heap_swap(i, j);
            i = j;
        }
    }
public:
    ArrayPtr<Block> max() {
        if (m_heap.empty()) return ArrayPtr<Block>::Nil;
        return *m_heap[0];
    }

    void insert(ArrayPtr<Block> elem) {
        std::size_t idx = m_heap.size();
        auto iter = m_location.emplace(elem, idx);
        if (!iter.second) return;

        m_heap.push_back(&iter.first->first);
        siftup(idx);
    }

    ArrayPtr<Block> extract_max() {
        if (m_heap.empty()) return ArrayPtr<Block>::Nil;
        ArrayPtr<Block> elem = *m_heap.front();

        heap_swap(0, m_heap.size() - 1);

        m_heap.pop_back();
        m_location.erase(elem);

        siftdown(0);

        return elem;
    }

    ArrayPtr<Block> erase(ArrayPtr<Block> &elem) {
        auto iter = m_location.find(elem);
        if (iter == m_location.end()) return ArrayPtr<Block>::Nil;

        ArrayPtr<Block> res = iter->first;
        std::size_t idx = iter->second;

        heap_swap(idx, m_heap.size() - 1);

        m_heap.pop_back();
        m_location.erase(iter);

        siftup(idx);
        siftdown(idx);

        return res;
    }

    void print() {
        std::cout << "Heap:\n";
        for (const ArrayPtr<Block> *el: m_heap) {
            const ArrayPtr<Block> &cp = *el;
            std::cout << "(" << (cp->start+1) << " -> " << (cp->start+cp->size) << ")\n";
        }
        std::cout << "Locations:\n";
        for (auto c : m_location) {
            std::cout << (c.first->start+1) << " at " << c.second << "\n";
        }
    }
};

class Allocator {
private:
    Heap m_heap;
    std::unordered_map<int, ArrayPtr<Block>> m_requests;

    void merge_next(ArrayPtr<Block> cur) {
        cur->size += cur->next->size;
        cur->next = cur->next->next;

        if (!cur->next.nil()) cur->next->prev = cur;
    }

    void insert(Block b) {
        *back = b;
        if (!back->next.nil()) back->next->prev = back;
        if (!back->prev.nil()) back->prev->next = back;

        m_heap.insert(back++);
    }

public:
    Allocator(int N) {
        insert({N});
    }

    int allocate(int req_id, int size) {
        if (m_heap.max().nil()) return -1;
        if (m_heap.max()->size < size) return -1;

        ArrayPtr<Block> cur = m_heap.extract_max();
        m_requests.emplace(req_id, cur);
        int block_size = cur->size;

        cur->taken = true;
        cur->size = size;

        if (block_size > size) {
            insert({
                .size = block_size - size,
                .start = cur->start + size,
                .prev = cur,
                .next = cur->next,
                .taken = false,
            });
        }
        
        return cur->start + 1;
    }

    void free(int req_id) {
        auto it = m_requests.find(req_id);
        if (it == m_requests.end()) return;

        ArrayPtr<Block> cur = it->second;
        m_requests.erase(it);

        cur->taken = false;
        
        if (!m_heap.erase(cur->prev).nil()) {
            cur = cur->prev;
            merge_next(cur);
        }

        if (!m_heap.erase(cur->next).nil()) {
            merge_next(cur);
        }

        m_heap.insert(cur);
    }

    void print() {
        std::cout << "Block chain:\n";
        for (ArrayPtr<Block> cur = 1; !cur.nil(); cur = cur->next) {
            std::cout << "#" << int(cur) << ": (" << (cur->start+1) << " -> " << (cur->start+cur->size) << "), taken = " << cur->taken << "\n";
        }
        m_heap.print();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    Allocator alloc(N);
    // alloc.print();

    for (int i = 0; i < M; i++) {
        int req;
        std::cin >> req;

        if (req > 0) {
            std::cout << alloc.allocate(i, req) << "\n";
        } else {
            alloc.free(-req-1);
        }
        // alloc.print();
    }
}
