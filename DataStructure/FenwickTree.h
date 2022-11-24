/**
 *  1D Fenwick Tree with - Template
 *  Note:
 *  - 0-based index
 *  - 
 * 
 *
 *  Tested:
 *  - https://codeforces.com/contest/52/problem/C
 *  - https://oj.vnoi.info/problem/qmax2
 *  - https://oj.vnoi.info/problem/lites
 *  - https://oj.vnoi.info/problem/segtree_itmix
 *  - https://atcoder.jp/contests/practice2/tasks/practice2_l
 *  - All Segment Tree problems in course Big-O Competitive Programming - Level 3
 */

template<class T> // T must support operator +, -
class FenwickTree {
public:
    vector<T> f;
    int n;

    FenwickTree(int n) : n(n), f(n + 1) {}

    void modify(int pos, T val) {
        while (pos <= n) {
            f[pos] += val;
            pos += pos & -pos;
        }
    }

    // update all element in range[l, r]
    void modify(int l, int r, T val) {
        this->modify(l, val);
        this->modify(r + 1, -val);
        this->modify(l, val * (l - 1));
        this->modify(r + 1, -val * r);
    }

    T get(int pos) {
        T res = 0;
        while (pos > 0) {
            res += f[pos];
            pos -= pos & -pos;
        }
        return res;
    }

    // get sum of elements in range [l, r]
    T get(int l, int r) {
        return this->get(r) - this->get(l - 1);
    }
};
