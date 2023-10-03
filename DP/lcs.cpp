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

vector<int> lcs(vector<int> &a, vector<int> &b, int m, int n) {
	int L[m + 1][n + 1];

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				L[i][j] = 0;
			else if (a[i - 1] == b[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;
			else
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}

	int index = L[m][n];
    vector<int> res;

	int i = m, j = n;
	while (i > 0 && j > 0) {
		if (a[i - 1] == b[j - 1]) {
			res.push_back(a[i-1]);
			i--;
			j--;
			index--;
		}
		else if (L[i - 1][j] > L[i][j - 1])
			i--;
		else
			j--;
	}
    reverse(all(res));

    return res;
}

void solve() {
    int m, n; cin >> m >> n;    
    vector<int> a(m), b(n);

    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<int> ans = lcs(a, b, m, n);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
        if (i != ans.size()-1) cout << " ";
    }

}

int main() {
    //setIO("lcs");
    int t = 1;
    //cin >> t;
    while (t--) solve();
}