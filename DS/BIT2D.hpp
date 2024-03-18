const int SZ = 1000 + 10;
struct BIT2D {
    int bit[SZ][SZ];

    int query(int x, int y) {
        int ans = 0;
        for (int i = x+1; i > 0; i -= -i & i) {
            for (int j = y+1; j > 0; j -= -j & j) {
                ans += bit[i][j];
            }
        }
        return ans;
    }

    void add(int x, int y, int val) {
        for (int i = x+1; i < SZ; i += -i & i) {
            for (int j = y+1; j < SZ; j += -j & j) {
                bit[i][j] += val;
            }
        }
    }

    void update(int x1, int y1, int x2, int y2, int val) {
        add(x1, y1, val);
        add(x1, y2+1, -val);
        add(x2+1, y1, -val);
        add(x2+1, y2+1, val);
    }
} bit;
