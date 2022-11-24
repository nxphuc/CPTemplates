/**
 *  Segment Tree with Lazy Propagation - Template
 *
 *  Tested:
 *  - https://codeforces.com/contest/52/problem/C
 *  - https://oj.vnoi.info/problem/qmax2
 *  - https://oj.vnoi.info/problem/lites
 *  - https://oj.vnoi.info/problem/segtree_itmix
 *  - https://atcoder.jp/contests/practice2/tasks/practice2_l
 *  - All Segment Tree problems in course Big-O Competitive Programming - Level 3
 */

template <
    class T,                                // data type
    T (*op)(const T &, const T &),          // operator to combine 2 child nodes
    T (*e)(),                               // identity element
    class F,                                // lazy node type
    F (*composition)(const F &, const F &), // operator to propagate infomation to child node
    T (*act)(const T &, const F &),         // apply lazy data to node
    F (*id)()                               // lazy identity element
>
class LazySegmentTree {
private:
    vector<T> seg;
    vector<F> lazy;
    int n, log, size;

    void build(const vector<T>& v, int idx, int l, int r) {
        if (l == r) {
            seg[idx] = v[l];
            return;
        }
        int m = (l + r) >> 1;
        build(v, 2 * idx + 1, l, m);
        build(v, 2 * idx + 2, m + 1, r);
        seg[idx] = op(seg[2 * idx + 1], seg[2 * idx + 2]);
    };

    void propagate(int idx, int left, int right) {
        if (lazy[idx] == id())
            return;
        seg[idx] = act(seg[idx], lazy[idx]);
        if (left != right) {
            lazy[2 * idx + 1] = composition(lazy[2 * idx + 1], lazy[idx]);
            lazy[2 * idx + 2] = composition(lazy[2 * idx + 2], lazy[idx]);
        }
        lazy[idx] = id();
    }

    void update(int idx, int left, int right, int from, int to, F val) {
        if (left > right)
            return;

        propagate(idx, left, right);
        if (left > to || right < from)
            return;

        if (from <= left && right <= to) {
            lazy[idx] = composition(lazy[idx], val);
            propagate(idx, left, right);
            return;
        }

        int mid = (left + right) >> 1;
        update(2 * idx + 1, left, mid, from, to, val);
        update(2 * idx + 2, mid + 1, right, from, to, val);
        seg[idx] = op(seg[idx * 2 + 1], seg[idx * 2 + 2]);
    }

    T query(int idx, int left, int right, int from, int to) {
        if (left > to || right < from)
            return e();
        propagate(idx, left, right);
        if (from <= left && right <= to)
            return seg[idx];
        int mid = (left + right) >> 1;
        return op(query(2 * idx + 1, left, mid, from, to), query(2 * idx + 2, mid + 1, right, from, to));
    }

public:
    explicit LazySegmentTree(int n) : LazySegmentTree(vector<T>(n, e())) {}

    explicit LazySegmentTree(const vector<T> &v) : n(v.size()) {
        log = ceil(log2(n));
        size = 1 << log;
        seg.assign(2 * size, e());
        lazy.assign(2 * size, id());
        build(v, 0, 0, n - 1);
    }

    void update(int from, int to, F val) {
        update(0, 0, n - 1, from, to, val);
    }

    T query(int from, int to) {
        return query(0, 0, n - 1, from, to);
    }
};

// Example usage

// Problem: VNOJ lites (https://oj.vnoi.info/problem/lites)
struct Ops {
    struct T { int on, off; };
    using F = int;

    static inline T op(const T &a, const T &b) { return {a.on + b.on, a.off + b.off}; }

    static inline T e() { return T({0, 1}); }

    static inline F id() { return F(0); }

    static inline F composition(const F &a, const F& b) { return a ^ b; }

    static inline T act(const T& a, const F& b) {
        if (b) return {a.off, a.on};
        return a;
    }
};

// shortern name
using LazySegTree = LazySegmentTree<Ops::T, Ops::op, Ops::e, Ops::F, Ops::composition, Ops::act, Ops::id>;