#include <bits/stdc++.h>
#include <math.h>
using namespace std;

struct node_t {
    int value;
    int count;
    node_t* left;
    node_t* right;
    node_t* parent;
};

node_t* build_tree(int from, int to) {
    if (from > to) return NULL;

    int median = (from + to) / 2;
    node_t* node = new node_t;
    
    node->value = median;
    node->count = 1;
    node->left = build_tree(from, median - 1);
    node->right = build_tree(median + 1, to);

    if (node->left) {
        node->left->parent = node;
        node->count += node->left->count;
    }

    if (node->right) {
        node->right->parent = node;
        node->count += node->right->count;
    }
    
    return node;
}

node_t* delete_node(node_t* root, int value) {
    if (!root || !root->left && !root->right) return NULL;
    
    if (value < root->value) root->left = delete_node(root->left, value);

    else if (value > root->value) root->right = delete_node(root->right, value);

    else if (root->left && root->right) {
        node_t* min = root->right;
        while (min->left) min = min->left;
        root->value = min->value;
        root->right = delete_node(root->right, min->value);
    }

    else {
        if (root->left) root = root->left;
        else root = root->right;
        root->count++;
    }

    root->count--;
    return root;
}

int select(node_t* node, int index) {
    if (!node->left && index == 0) return node->value;
    if (!node->left) return select(node->right, index - 1);

    if (node->left->count == index) return node->value;
    if (node->left->count > index) return select(node->left, index);
    return select(node->right, index - node->left->count - 1);
}

void print(node_t* node, int depth = 0) {
    if (!node) {
        cout << "NULL" << '\n';
        return;
    }
    for (int i = 0; i < depth; i++) cout << ' ';
    cout << node->value << "; " << node->count << '\n';
    if (node->left) print(node->left, depth + 1);
    if (node->right) print(node->right, depth + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    node_t* root = build_tree(1, N);
    root->parent = NULL;

    int current = 0;
    while (N > 0) {
        current = (current + K - 1) % N;
        int val = select(root, current);
        root = delete_node(root, val);
        cout << val << ' ';
        N--; 
    }

    cout << '\n';
}