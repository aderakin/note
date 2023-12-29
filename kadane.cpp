    vector<int> a(n);
    for (int &i : a) cin >> i;
 
    int res = a[0];
    int sum = 0;
    for (int x : a) {
        sum = max(sum + x, x);
        ckmax(res, sum);
    }
 
    cout << res;