/*
========================================
Problem  : Magic of the locker
URL      : https://www.spoj.com/problems/LOCKER
Code     : https://github.com/whoashish115/spoj
Author   : Ashish Kumar
Language : C++23
========================================
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;

ll modpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    ll n;
    cin >> n;

    if (n <= 3) {
        cout << n << '\n';
        return;
    }

    if (n % 3 == 0) {
        cout << modpow(3, n / 3) << '\n';
    } else if (n % 3 == 1) {
        cout << 4 * modpow(3, (n - 4) / 3) % MOD << '\n';
    } else {
        cout << 2 * modpow(3, (n - 2) / 3) % MOD << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}