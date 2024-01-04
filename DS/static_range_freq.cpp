int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int N, Q;
  cin >> N >> Q;

  unordered_map<int, vector<int>> pos;
  pos.reserve(N * 4);
  rep(i, 0, N) {
    int a;
    cin >> a;
    pos[a].pb(i);
  }

  while (Q--) {
    int l, r, x;
    cin >> l >> r >> x;
    if (!pos.count(x)) {
      cout << "0\n";
    } else {
      auto& v = pos[x];
      cout << lower_bound(all(v), r) - lower_bound(all(v), l) << '\n';
    }
  }

  return 0;
}