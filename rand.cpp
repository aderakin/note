#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long get_rand(long long r) {
    return uniform_int_distribution<long long> (0, r-1)(rng);
}