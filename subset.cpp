#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void ssbf() {
    int n;
    for (int msk = 0; msk < (1 << n); msk++) {

    // get the subset
        for (int i = 0; i < n; i++) {
            // Check if the ith bit is toggled
            if (msk & (1 << i)) {
            } 
        }
    }

}

void comb(int N, int K) {
    string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) cout << " " << i;
        }
        cout << endl;
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
}

int n; 
vector<ll> p;
ll L, R;

vector<ll> ans;

// gen all prod in [L, R]
void gen(int pos, ll cur) {
    if (cur > R || pos >= n) return;
    if (cur >= L) ans.push_back(cur); 

    ll new_cur = cur * p[pos];

    gen(pos, new_cur);
    gen(pos + 1, cur);
}
