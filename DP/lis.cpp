#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end()

void setIO(string name = ""){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (!name.empty()) {
        freopen((name + ".inp").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }

}

const int inf = 1e9;

vector<int> lis(vector<int> &a) {
    int n = (int) a.size();
    vector<int> d, trace;
    vector<int> f(n + 1, inf);
    f[0] = -inf;

    int len = 0;
    for(int i = 0; i < n; i++) {
        int k = lower_bound(f.begin(), f.end(), a[i]) - f.begin();
        f[k] = a[i];
        len = max(len, k);
        d.push_back(k);
    }

    while(len) {
        for (int i = n - 1; i >= 0; i--) {
            if(d[i] == len) {
                trace.push_back(i);
                n = i;
                break;
            }
        }
        len--;
    }

    reverse(trace.begin(), trace.end());
	return trace;
}
 
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
 
    vector<int> ans = lis(a);
 
    cout << ans.size() << endl;
    for (auto i: ans) cout << i+1 << " ";
}


int main() {
    setIO("LIS");
    int t = 1;
    //cin >> t;
    while (t--) solve();
}