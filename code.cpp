#include <bits/stdc++.h>
using namespace std;

// Parse the expanded preorder directly and record parent/depth
static void parse_and_record(const vector<int>& pre, int& idx, int parentVal, int depth,
                             vector<int>& parent, vector<int>& dep) {
    if (idx >= (int)pre.size()) return;
    int v = pre[idx++];
    if (v == -1) return; // null node
    if (v >= 0 && v < (int)parent.size()) {
        parent[v] = parentVal;
        dep[v] = depth;
    }
    // left subtree
    parse_and_record(pre, idx, v, depth + 1, parent, dep);
    // right subtree
    parse_and_record(pre, idx, v, depth + 1, parent, dep);
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

    // Value range is 1..1000; use arrays for speed and to avoid allocations
    vector<int> parentArr(1001, INT_MIN);
    vector<int> depArr(1001, INT_MIN);

    int idx = 0;
    parse_and_record(pre, idx, -1, 0, parentArr, depArr);

    for (auto [x, y] : queries) {
        if (x < 0 || x >= (int)parentArr.size() || y < 0 || y >= (int)parentArr.size()) {
            cout << 0 << '\n';
            continue;
        }
        if (depArr[x] == INT_MIN || depArr[y] == INT_MIN) {
            cout << 0 << '\n';
            continue;
        }
        int dx = depArr[x];
        int dy = depArr[y];
        int px = parentArr[x];
        int py = parentArr[y];
        cout << ((dx == dy && px != py) ? 1 : 0) << '\n';
    }

    return 0;
}
