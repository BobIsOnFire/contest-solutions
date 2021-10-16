struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;
        
        for (int i = lists.size() / 2 - 1; i >= 0; --i) {
            siftdown(lists, i);
        }
        
        if (lists[0] == nullptr) return nullptr;
        
        ListNode* start = lists[0];
        ListNode* curr = start;
        lists[0] = lists[0]->next;
        siftdown(lists, 0);
        
        while (lists[0] != nullptr) {
            curr->next = lists[0];
            curr = curr->next;
            lists[0] = lists[0]->next;
            siftdown(lists, 0);
        }
        
        return start;
    }
private:
    void print(ListNode* node) {
        while (node) {
            cout << node->val << " ";
            node = node->next;
        }
        cout << "\n";
    }
    
    void print(vector<ListNode*>& lists) {
        for (int i = 0; i < lists.size(); i++) {
            print(lists[i]);
        }
    }
    
    int left(int i) {
        return 2i + 1;
    }

    int right(int i) {
        return 2i + 2;
    }

    int parent(int i) {
        return (i - 1) / 2;
    }
    
    int val(ListNode* node) {
        if (!node) return (int) 0x7FFFFFFF;
        return node->val;
    }
    
    void siftdown(vector<ListNode*>& lists, int i) {
        int j = i;
        while (true) {
            if (left(i) < lists.size() && val(lists[j]) > val(lists[left(i)])) {
                j = left(i);
            }
            if (right(i) < lists.size() && val(lists[j]) > val(lists[right(i)])) {
                j = right(i);
            }
            if (i == j) break;
            swap(lists[i], lists[j]);
            i = j;
        }
    }
};