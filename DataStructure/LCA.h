/**
 * Lowest common ancestor - Template
 * 0-based index
 */

class LCA {
private:
    vector<int> tin, tout;
    vector<vector<int>> par, adj;
    int n, root, counter, lg;

    void dfs(int u, int p) {
        tin[u] = ++counter;

        par[u][0] = p;
        for (int v : adj[u])
            if (v != p)
                dfs(v, u);

        tout[u] = ++counter;
    }
public:
    LCA(int _n, const vector<vector<int>>& _adj, int _root = 0)
            : n(n), root(_root), adj(_adj) {
        lg = ceil(log2(n));
        tin.assign(n, 0);
        tout.assign(n, 0);
        par.assign(n, vector<int>(lg + 1, root));

        dfs(root, root);

        for (int k = 1; k <= lg; k++)
            for (int i = 0; i < n; i++)
                par[i][k] = par[par[i][k - 1]][k - 1];
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tin[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;

        for (int k = lg; k >= 0; k--)
            if (!isAncestor(par[u][k], v))
                u = par[u][k];
        return par[u][0];
    }
};
