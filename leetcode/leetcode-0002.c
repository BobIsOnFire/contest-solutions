struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode nodes[100];


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode self = {0, &self};
    
    int rem = 0;
    int i = -1;
    int l1_goes = 1;
    int l2_goes = 1;

    for (; l1_goes || l2_goes; l1 = l1->next, l2 = l2->next) {
        i++;
        
        if (!l1) {
            l1_goes = 0;
            l1 = &self;
        }
        
        if (!l2) {
            l2_goes = 0;
            l2 = &self;
        }
        
        int sum = rem + l1->val + l2->val;
        rem = sum / 10;
        nodes[i].val = sum % 10;
        nodes[i].next = &nodes[i+1];
    }
    
    if (nodes[i].val == 0) i--;
    nodes[i].next = NULL;
    
    return &nodes[0];
}