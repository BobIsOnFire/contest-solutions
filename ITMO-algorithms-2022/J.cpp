#include <bits/stdc++.h>

class List {

private:
    static struct ListNode {
        int value;
        ListNode *next;
        ListNode *prev;
    } nodes[100000];
    static int node_idx;

    int length = 0;
    ListNode *head = NULL;
    ListNode *tail = NULL;
    ListNode *mid = NULL;

    void insert_after(ListNode *after, int value) {
        nodes[node_idx] = {value, after->next, after};

        if (after->next) after->next->prev = &nodes[node_idx];
        after->next = &nodes[node_idx];

        node_idx++;
    }

    ListNode* remove(ListNode *node) {
        if (node->next) node->next->prev = node->prev;
        if (node->prev) node->prev->next = node->next;

        return node;
    }

    void initialize(int value) {
        nodes[node_idx] = {value, NULL, NULL};

        head = &nodes[node_idx];
        mid = &nodes[node_idx];
        tail = &nodes[node_idx];
        length = 1;

        node_idx++;
    } 

public:
    void insert_tail(int value) {
        if (head == NULL) {
            initialize(value);
            return;
        }

        insert_after(tail, value);

        if (length % 2 == 0) mid = mid->next;
        tail = tail->next;
        length++;
    }

    void insert_mid(int value) {
        if (head == NULL) {
            initialize(value);
            return;
        }

        if (length == 1) {
            insert_tail(value);
            return;
        }

        insert_after(mid, value);

        if (length % 2 == 0) mid = mid->next;
        length++;
    }

    int remove_head() {
        ListNode *node = remove(head);

        head = node->next;
        if (length % 2 == 0) mid = mid->next;
        length--;

        return node->value;
    }
};

List::ListNode List::nodes[100000] = {};
int List::node_idx = 0;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N;
    std::cin >> N;

    List queue;
    for (int i = 0; i < N; i++) {
        char ch;
        std::cin >> ch;

        if (ch == '-') {
            std::cout << queue.remove_head() << "\n";
            continue;
        }

        int a;
        std::cin >> a;

        if (ch == '+') {
            queue.insert_tail(a);
        } else {
            queue.insert_mid(a);
        }
    }
}
