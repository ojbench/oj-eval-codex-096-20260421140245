#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

Node* buildTree(const vector<int>& pre, int& idx) {
    if (idx >= (int)pre.size()) return nullptr;
    int v = pre[idx++];
    if (v == -1) return nullptr;
    Node* root = new Node(v);
    root->left = buildTree(pre, idx);
    root->right = buildTree(pre, idx);
    return root;
}

void dfs(Node* node, int parentVal, int depth,
         unordered_map<int,int>& parent,
         unordered_map<int,int>& dep) {
    if (!node) return;
    parent[node->val] = parentVal;
    dep[node->val] = depth;
    dfs(node->left, node->val, depth + 1, parent, dep);
    dfs(node->right, node->val, depth + 1, parent, dep);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;
    vector<pair<int,int>> queries;
    queries.reserve(max(1, q));
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        queries.emplace_back(x, y);
    }

    vector<int> pre;
    pre.reserve(1024);
    int t;
    while (cin >> t) pre.push_back(t);

    int idx = 0;
    Node* root = buildTree(pre, idx);

    unordered_map<int,int> parent;
    unordered_map<int,int> dep;
    dfs(root, -1, 0, parent, dep);

    for (auto [x, y] : queries) {
        auto itx = dep.find(x);
        auto ity = dep.find(y);
        if (itx == dep.end() || ity == dep.end()) {
            cout << 0 << '\n';
            continue;
        }
        int dx = itx->second;
        int dy = ity->second;
        int px = parent[x];
        int py = parent[y];
        cout << ((dx == dy && px != py) ? 1 : 0) << '\n';
    }

    return 0;
}

