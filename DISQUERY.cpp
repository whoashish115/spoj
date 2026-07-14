/*
========================================
Problem  : Distance Query
URL      : https://www.spoj.com/problems/DISQUERY
Code     : https://github.com/whoashish115/spoj
Author   : Ashish Kumar
Language : C++23
========================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAX_BITS = 20;
const int INF = 1e9;

vector<pair<int, int>> adj[MAXN];
int up[MAXN][MAX_BITS];
int mx[MAXN][MAX_BITS];
int mn[MAXN][MAX_BITS];
int depthArr[MAXN];

void dfs(int u, int p, int edge_weight) {
    up[u][0] = p;
    mx[u][0] = edge_weight;
    mn[u][0] = edge_weight;

    for (int i = 1; i < MAX_BITS; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        mx[u][i] = max(mx[u][i - 1], mx[up[u][i - 1]][i - 1]);
        mn[u][i] = min(mn[u][i - 1], mn[up[u][i - 1]][i - 1]);
    }

    for (auto edge : adj[u]) {
        int v = edge.first;
        int weight = edge.second;
        if (v != p) {
            depthArr[v] = depthArr[u] + 1;
            dfs(v, u, weight);
        }
    }
}

void query(int u, int v) {
    int ans_min = INF;
    int ans_max = -INF;

    if (depthArr[u] < depthArr[v]) swap(u, v);

    int diff = depthArr[u] - depthArr[v];
    for (int i = 0; i < MAX_BITS; i++) {
        if ((diff >> i) & 1) {
            ans_min = min(ans_min, mn[u][i]);
            ans_max = max(ans_max, mx[u][i]);
            u = up[u][i];
        }
    }

    // when one node was ancestor of the other
    if (u == v) {
        cout << ans_min << " " << ans_max << "\n";
        return;
    }

    // lift both nodes together
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            ans_min = min(ans_min, min(mn[u][i], mn[v][i]));
            ans_max = max(ans_max, max(mx[u][i], mx[v][i]));
            u = up[u][i];
            v = up[v][i];
        }
    }

    ans_min = min(ans_min, min(mn[u][0], mn[v][0]));
    ans_max = max(ans_max, max(mx[u][0], mx[v][0]));

    cout << ans_min << " " << ans_max << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    depthArr[1] = 0;
    for (int i = 0; i < MAX_BITS; i++) {
        mn[0][i] = INF;
        mx[0][i] = -INF;
    }

    dfs(1, 0, INF);

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        query(u, v);
    }

    return 0;
}