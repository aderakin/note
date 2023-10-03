#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

struct pt {
    ld x, y;
};

struct line {
    ld a, b, c;
};

const ld EPS = 1e-9;

ld det(ld a, ld b, ld c, ld d) {
    return a*d - b*c;
}

bool intersect(line m, line n, pt & res) {
    ld zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS)
        return false;
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}