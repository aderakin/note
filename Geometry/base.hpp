#ifndef EPS  // allow test files to overwrite EPS
#define EPS 1e-6
#endif

const double PI = acos(-1.0l);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int sgn(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

// for int types
template<typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type * = nullptr>
inline int sgn(T a, T b) {
    return (a == b) ? 0 : (a < b) ? -1 : 1;
}

template <class T>
struct P {
    T x, y;
    explicit P(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }

    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }

    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }

    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }  // makes dist()=1
    P perp() const { return P(-y, x); }        // rotates +90 degrees
    P normal() const { return perp().unit(); }

    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend istream& operator>>(istream& in, P<T>& p) {
        in >> p.x >> p.y;
        return in;
    }
    friend ostream& operator<<(ostream& out, P p) {
        return out << "(" << p.x << "," << p.y << ")";
    }
};

using Point = P<double>;
using PointInt = P<long long>;

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

// min of directed angle AOB & BOA
double angle(Point a, Point o, Point b) { 
    a = a - o; b = b - o;
    return acos((a.dot(b)) / a.dist() / b.dist());
}

// angle AOB, in range [0, 2*PI)
double directed_angle(Point a, Point o, Point b) { 
    double t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
}

// Distance from p to Line ab 
template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}

// Distance from p to Line ab (closest Point --> c)
// c is projection of p on AB
double lineDist(const Point& a, const Point& b, const Point& p, Point& c) {
    Point ap = p - a, ab = b - a;
    double u = (ap.dot(ab)) / ab.dist2();
    c = a + (ab*u);
    return (p-c).dist();
}

// returns true if p is on segment [a, b]
template<class P> bool onSegment(P a, P b, P p) {
	return p.cross(a, b) == 0 && (a - p).dot(b - p) <= 0;
}
