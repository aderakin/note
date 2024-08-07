#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end()

const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;

ll binpow(ll a, ll n, ll m = MOD) {
    a %= m;
    ll res = 1;

    while (n) {
        if (n & 1) res = res * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return res;
}

ll fac[MAXN+1];
ll inv[MAXN+1];

ll nCr(int n, int r) { 
    if (n < r) return 0;
    return fac[n] * inv[r] % MOD * inv[n - r] % MOD; 
}

void _precalc() {
    fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) { 
        fac[i] = fac[i - 1] * i % MOD; 
    }

    inv[MAXN] = binpow(fac[MAXN], MOD - 2, MOD);
	for (int i = MAXN; i >= 1; i--) { 
        inv[i - 1] = inv[i] * i % MOD; 
    }

}

// O(n^1/2)
map<int, int> factor(int x) {
	map<int, int> ret;
	for (int i = 2; i * i <= x; i++) {
		while (x % i == 0) {
            ret[i]++;
			x /= i;
		}
	}
	if (x > 1) { ret[x]++; }
	return ret;
} 

int v_p(int n, int p) {
    int ans = 0;

    while (n) {
        n /= p;
        ans += n;
    }

    return ans;
}

int max_div[];

void fc() {
    for (int i = 2; i < MAXN; i++) {
        if (max_div[i] == 0) {
            for (int j = i; j < MAXN; j+=i) {
                max_div[j] = i;
            }
        }
    }


    int x;
    int div_num = 1;
    
    while (x != 1) {
        int pr = max_div[x];
        int cnt = 0;
        while (x % pr == 0) {
            cnt++;
            x /= pr;
        }
        div_num *= (cnt + 1);
    }
    
    cout << div_num << '\n';
}

int mu[MAXN];

void muy() {
    mu[1] = 1;
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 2*i; j <= MAXN; j += i) mu[j] -= mu[i];
    }
}

int phi(int n) {
    if (n == 0) return 0;
    int ans = n;
    
    while (n != 1) {
        int prime = max_div[n];
        while (n % prime == 0) {
            n /= prime;
        }

        ans -= ans / prime;
    }

    return ans;
}

void _precalc() {
    REP(i, MAXN-1) {
        phi[i] = i;
    }

    REP(i, MAXN-1) {
        for (int j = 2*i; j < MAXN; j += i) {
            phi[j] -= phi[i];
        }
    }
}