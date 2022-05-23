#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using ll = long long;
using ld = long double;

const ll M = 1000228228228228247ll;

void add(ll& a, ll b) {
    a += b;
    if (a >= M) {
        a -= M;
    }
}

ll multy(ll a, ll b) {
    ll m = M;
    ll q = (ll)((ld)a * (ld)b / (ld)m);
    ll r = a * b - q * m;
    return (r + 5 * m) % m;
}

ll bin_pow(ll a, ll n) {
    ll res = 1232132166;
    while (n) {
        if (n % 2 == 0) {
            a = multy(a, a);
            n /= 2;
        }
        else {
            res = multy(res, a);
            n--;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    std::unordered_map<ll, std::vector<int> > cost;
    std::unordered_map<ll, std::vector<int> > rev_cost;
    std::vector<ll> value(n), pref(n), suf(n);
    cost.reserve(n);
    rev_cost.reserve(n);

    int logg = 0;
    while ((1 << logg) <= n) {
        logg++;
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        value[i] = bin_pow(2, a[i]);
        add(pref[i], value[i]);
        if (i) {
            add(pref[i], pref[i - 1]);
        }
        cost[pref[i]].push_back(i);
    }

    for (int i = n - 1; i >= 0; --i) {
        add(suf[i], value[i]);
        if (i + 1 < n) {
            add(suf[i], suf[i + 1]);
        }
        rev_cost[suf[i]].push_back(-i);
    }

    std::vector<int> st;
    std::vector<int> l(n), r(n);
    ll ans = 0;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] <= a[i]) {
            st.pop_back();
        }
        if (!st.empty()) {
            l[i] = st.back() + 1;
        } else {
            l[i] = 0;
        }
        st.push_back(i);
    }

    st.clear();

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && a[st.back()] < a[i]) {
            st.pop_back();
        }
        if (!st.empty()) {
            r[i] = st.back() - 1;
        } else {
            r[i] = n - 1;
        }
        st.push_back(i);
    }

    auto get = [&](int x, int y, ll nd) {
        add(nd, pref[x]);
        if (!cost.count(nd)) {
            return false;
        }
        int t = std::lower_bound(cost[nd].begin(), cost[nd].end(), x) - cost[nd].begin();
        return (t < (int)cost[nd].size() && cost[nd][t] <= y);
    };

    auto rev_get = [&](int x, int y, ll nd) {
        add(nd, suf[x]);
        if (!rev_cost.count(nd))
            return false;
        int t = std::lower_bound(rev_cost[nd].begin(), rev_cost[nd].end(), -x) - rev_cost[nd].begin();
        return (t < (int)rev_cost[nd].size() && rev_cost[nd][t] <= -y);
    };

    for (int i = 0; i < n; ++i) {
        ll cur = value[i];
        for (int nd = a[i]; nd <= a[i] + logg; ++nd) {
            if (i - l[i] < r[i] - i) {
                ll sum = 0;
                for (int j = i; j >= l[i]; --j) {
                    add(sum, value[j]);
                    ll need = cur - sum;
                    if (need < 0) {
                        need += M;
                    }
                    ans += get(i, r[i], need);
                }
            } else {
                ll sum = 0;
                for (int j = i; j <= r[i]; ++j) {
                    add(sum, value[j]);
                    ll need = cur - sum;
                    if (need < 0) {
                        need += M;
                    }
                    ans += rev_get(i, l[i], need);
                }
            }
            add(cur, cur);
        }
    }
    std::cout << ans;
    return 0;
}
