/*
========================================
Problem  : QTREE2 - Query on a tree II
URL      : https://www.spoj.com/problems/QTREE2
Code     : https://github.com/whoashish115/spoj
Author   : Ashish Kumar
Language : C++23
========================================
*/


#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10005;
const int MAX_BITS = 15;

vector<pair<int,int>> adj[MAX_N];
int up[MAX_N][MAX_BITS];
int depthArr[MAX_N];
long long distArr[MAX_N];

void dfs(int u, int parent) {
    up[u][0] = parent;

    for (int j = 1; j < MAX_BITS; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }

    for (auto [v, w] : adj[u]) {
        if (v == parent) continue;

        depthArr[v] = depthArr[u] + 1;
        distArr[v] = distArr[u] + w;

        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (depthArr[u] < depthArr[v]) swap(u, v);

    int diff = depthArr[u] - depthArr[v];
    for (int j = 0; j < MAX_BITS; j++) {
        if (diff & (1 << j)) u = up[u][j];
    }

    if (u == v) return u;

    for (int j = MAX_BITS - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

long long distance_nodes(int u, int v) {
    int g = lca(u, v);
    return distArr[u] + distArr[v] - 2LL * distArr[g];
}

int jump(int u, int k) {
    for (int j = 0; j < MAX_BITS; j++) {
        if (k & (1 << j)) u = up[u][j];
    }
    return u;
}

int kth(int u, int v, int k) {
    int g = lca(u, v);
    int left = depthArr[u] - depthArr[g];
    int right = depthArr[v] - depthArr[g];

    if (k <= left + 1) {
        return jump(u, k - 1);
    } else {
        int rem = k - (left + 1);
        return jump(v, right - rem);
    }
}

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        depthArr[i] = 0;
        distArr[i] = 0;
        for (int j = 0; j < MAX_BITS; j++) up[i][j] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    dfs(1, 0);

    string cmd;
    while (cin >> cmd) {
        if (cmd == "DONE") break;

        if (cmd == "DIST") {
            int a, b;
            cin >> a >> b;
            cout << distance_nodes(a, b) << '\n';
        } else if (cmd == "KTH") {
            int a, b, k;
            cin >> a >> b >> k;
            cout << kth(a, b, k) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
        if (t) cout << '\n';
    }

    return 0;
}