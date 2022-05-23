#include <unordered_map>
#include <vector>

template<class T>
class Heap {
private:
    std::vector<const T*> m_heap;
    std::unordered_map<T, std::size_t> m_location;

    std::size_t parent(std::size_t i) { return (i - 1) / 2; }
    std::size_t left(std::size_t i) { return 2 * i + 1; }
    std::size_t right(std::size_t i) { return 2 * i + 2; }

    void heap_swap(std::size_t i, std::size_t j) {
        std::swap(m_heap[i], m_heap[j]);
        m_location[*m_heap[i]] = i;
        m_location[*m_heap[j]] = j;
    }

    void siftup(std::size_t i) {
        while (i > 0 && *m_heap[parent(i)] < *m_heap[i]) {
            heap_swap(i, parent(i));
            i = parent(i);
        }
    }

    void siftdown(std::size_t i) {
        std::size_t j = i;
        std::size_t n = m_heap.size();
        while (true) {
            if (left(i) < n && *m_heap[i] < *m_heap[left(i)]) {
                j = left(i);
            }
            if (right(i) < n && *m_heap[i] < *m_heap[right(i)]) {
                j = right(i);
            }
            if (i == j) break;
            heap_swap(i, j);
            i = j;
        }
    }
public:
    T& max() {
        return *m_heap[0];
    }

    void insert(T && elem) {
        std::size_t idx = m_heap.size();
        auto iter = m_location.emplace(std::move(elem), idx);
        if (!iter.second) return;

        m_heap.push_back(&iter.first->first);
        siftup(idx);
    }

    T extract_max() {
        T elem = *m_heap.front();
        m_location.erase(elem);

        heap_swap(0, m_heap.size() - 1);
        m_heap.pop_back();
        siftdown(0);

        return elem;
    }

    T erase(T& elem) {
        auto iter = m_location.find(elem);
        if (iter == m_location.end()) return -1;

        T res = iter->first;
        std::size_t idx = iter->second;
        m_location.erase(iter);

        heap_swap(idx, m_heap.size() - 1);
        m_heap.pop_back();
        siftdown(idx);
        siftup(idx);

        return res;
    }
};
