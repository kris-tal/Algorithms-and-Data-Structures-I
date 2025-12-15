#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

struct edge {
    int vert;
    int weight;
    int interval;
    int beg;
    int end;

    edge(int v, int w, int i, int b, int e) : vert(v), weight(w), interval(i), beg(b), end(e) {}
};

struct qe {
    int vert;
    long long dist;

    qe(int v, int d) : vert(v), dist(d) {}
};

struct cmp {
    bool operator()(const qe& a, const qe& b) {
        return a.dist > b.dist;
    }
};

void dijkstra(int s, int k, std::vector<std::vector<edge>> &graph, int N) {
    std::priority_queue<qe, std::vector<qe>, cmp> q;
    std::vector<long long> D(N, LLONG_MAX);

    D[s] = 0;
    q.push(qe(D[s], s));
    while(!q.empty()) {
        auto[v, dv] = q.top();
        q.pop();
        if(dv != D[v]) continue;        // ?
        for(auto [u, d, t, a, l] : graph[v]) {
            if(!(t == 0 && a == 0 && l == 0)) {
                if((D[v] - a + t) % t >= l) {
                    if((D[v] + t) % t < a) d += a - (D[v] + t) % t;
                    else d += t - (D[v] % t) + a;
                }
            }
            if(D[u] > D[v] + d) {
                D[u] = D[v] + d;
                q.push(qe(u, D[u]));
            }
        }
    }
    if(D[k] != LLONG_MAX) std::cout <<  D[k] << "\n";
    else std::cout << "NIE\n";
}

int main() {
    int q;
    std::cin >> q;

    while(q--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<edge>> graph(n);

        for(int i = 0; i < m; i++) {
            int u, v, w, t, a, l;
            std::cin >> u >> v >> w >> t >> a >> l;
            u--;
            v--;
            graph[u].push_back(edge(v, w, t, a, l));
        }

        dijkstra(0, n - 1, graph, n);
    }

    return 0;
}
