/**
 * Dinic's Algorithm
 *
 * Usage:
 * Default index from 0
 * Dinic flow(n) (or Dinic flow(n+1) if your network index from 1)
 * flow.add(u, v, capacity)
 * Get maximum flow from s to t: flow.getFlow(s, t)
 * 
 * Complexity: O(E*V^2)
*/

const int INF = 1e9;

struct Edge {
    int u, v, cap, flow;
    Edge(int u = 0, int v = 0, int cap = 0) : u(u), v(v), cap(cap), flow(0) {}
};

// graph index from 0
struct Dinic {
    int n, s, t;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> iter, level;

    Dinic(int n) : n(n), graph(n), iter(n), level(n) {}

    void addEdge(int u, int v, int cap) {
        graph[u].push_back(edges.size());
        edges.push_back({u, v, cap});
        graph[v].push_back(edges.size());
        edges.push_back({v, u, 0});
    }

    int getFlow(int _s, int _t) {
        s = _s, t = _t;
        int newFlow, sumFlow = 0;
        while (bfs()) {
            fill(iter.begin(), iter.end(), 0);
            while (newFlow = dfs(s, t, INF)) {
                sumFlow += newFlow;
            }
        }
        return sumFlow;
    }
private:
    int bfs() {
        queue<int> q;
        q.push(s);
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i : graph[u]) {
                if (level[edges[i].v] != -1) continue;
                if (edges[i].cap <= edges[i].flow) continue;
                level[edges[i].v] = level[u] + 1;
                q.push(edges[i].v);
            }
        }
        return level[t] != -1;
    }

    int dfs(int s, int t, int pushed) {
        if (pushed == 0) return 0;
        if (s == t) return pushed;
        for (int &i = iter[s]; i < graph[s].size(); i++) {
            int id = graph[s][i];
            int v = edges[id].v;
            if (level[v] != level[s] + 1) continue;
            if (edges[id].cap <= edges[id].flow) continue;
            int f = min(pushed, edges[id].cap - edges[id].flow);
            f = dfs(v, t, f);
            if (f == 0) continue;
            edges[id].flow += f;
            edges[id ^ 1].flow -= f;
            return f;
        }
        return 0;
    }
};