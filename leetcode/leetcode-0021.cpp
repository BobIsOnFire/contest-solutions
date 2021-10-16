struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        
        smart_swap(l1, l2);
        ListNode *start = l1;
        l1 = l1->next;
        
        ListNode *curr = start;

        while (l1 != nullptr && l2 != nullptr) {
            smart_swap(l1, l2);
            curr->next = l1;
            l1 = l1->next;
            curr = curr->next;
        }
        
        if (l1 == nullptr) curr->next = l2;
        else if (l2 == nullptr) curr->next = l1;
        
        return start;
    }
private:
    void smart_swap(ListNode*& l1, ListNode*& l2) { 
        if (l1->val > l2->val) swap(l1, l2);
    }
};