array<T, 3> extgcd(T a, T b) {
    array x{T{1}, T{0}};
    while (b) {
        x[0] = exchange(x[1], x[0] - a / b * x[1]);
        a = exchange(b, a % b);
    }
    return {x[0], x[1], a};
}
