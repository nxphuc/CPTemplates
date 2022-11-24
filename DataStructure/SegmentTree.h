/**
 *  Basic Segment Tree - Template
 *
 *  Tested:
 *  - https://codeforces.com/contest/61/problem/E
 *  - https://codeforces.com/contest/380/problem/C
 *  - https://codeforces.com/contest/474/problem/F
 *  - All Segment Tree problems in course Big-O Competitive Programming - Level 3
 */

template<
    class T,                      // data type
    T (*op) (const T&, const T&), // operator to combine 2 child nodes
    T (*e) ()                     // identity element
>
class SegmentTree{
private:
    vector<T> seg;
    int n, log, size;

    void update(int id, int l, int r, int p, T v) {
        if (l == r) {
            seg[id] = v;
            return;
        }
        int m = (l + r) >> 1;
        if (m >= p)
            update(2 * id + 1, l, m, p, v);
        else
            update(2 * id + 2, m + 1, r, p, v);
        seg[id] = op(seg[2 * id + 1], seg[2 * id + 2]);
    }

    T query(int id, int l, int r, int u, int v) {
        if (v < l || u > r)
            return e();
        if (u <= l && r <= v)
            return seg[id];
        int m = (l + r) >> 1;
        return op(query(2 * id + 1, l, m, u, v), query(2 * id + 2, m + 1, r, u, v));
    }

    void build(const vector<T>& v, int id, int l, int r) {
        if (l == r) {
            seg[id] = v[l];
            return;
        }
        int m = (l + r) >> 1;
        build(v, 2 * id + 1, l, m);
        build(v, 2 * id + 2, m + 1, r);
        seg[id] = op(seg[2 * id + 1], seg[2 * id + 2]);
    };
public:
    explicit SegmentTree(int n = 0) : SegmentTree(vector<T>(n, e())) {}

    explicit SegmentTree(const vector<T>& v) : n(v.size()) {
        log = ceil(log2(n));
        size = 1 << log;
        seg = vector<T>(2 * size);
        build(v, 0, 0, n - 1);
    }

    void update(int pos, T val) {
        update(0, 0, n - 1, pos, val);
    }

    T query(int from, int to) {
        return query(0, 0, n - 1, from, to);
    }
};

// Example usage:

// CodeForces 61D - Enemy is weak (https://codeforces.com/contest/61/problem/E)
struct Ops {
    using T = int;
    inline static T op(const T& a, const T& b) {
        return a + b;
    }

    inline static T e() { return 0; }
};

using SegTree = SegmentTree<Ops::T, Ops::op, Ops::e>;