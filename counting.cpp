#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end()

const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;

ll binpow(ll a, ll n, ll m) {
    a %= m;
    ll res = 1;

    while (n > 0) {
        if (n & 1) res = res * a % m;
        a = a * a % m;
        n /= 2;
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
map<int, int> factor(int n) {
	map<int, int> ret;
	for (int i = 2; i * i <= n; i++) {
		while (n % i == 0) {
            ret[i]++;
			n /= i;
		}
	}
	if (n > 1) { ret[n]++; }
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
        int prime = max_div[x];
        int count = 0;
        while (x % prime == 0) {
            count++;
            x /= prime;
        }
        div_num *= count + 1;
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