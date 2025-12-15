#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stack>
#include <map>
#include <iomanip>
#include <climits>

struct edge {
    int vert;
    long long dist;
};

bool relax(int u, int v, long long dist, std::vector<long long> &D) {
    if(D[v] > D[u] + dist) {
        D[v] = D[u] + dist;
        return true;
    }
    return false;
}

void bellman_ford(std::vector<long long> &D, std::vector<std::vector<edge>> &graph, int n) {
    D[n] = 0;

    bool relaxed = true;
    for(int i = 0; i < n + 1 && relaxed; i++) {
        relaxed = false;
        for(int u = n; u >= 0; u--) {
            for(auto v : graph[u]) {
                relax(u, v.vert, v.dist, D);
            }
        }
    }
}

struct cmp {
    bool operator()(const edge &a, const edge &b) {
        return a.dist > b.dist;
    }
};

void dijkstra(int s, const std::vector<long long> &BF, std::vector<std::vector<edge>> &graph, int n) {
    std::vector<long long> D(n + 1, LLONG_MAX);
    std::priority_queue<edge, std::vector<edge>, cmp> q;
    D[s] = 0;

    q.push({s, D[s]});
    while(!q.empty()) {
        auto [v, dv] = q.top();
        q.pop();
        if(dv != D[v]) continue;
        for(auto [u, d] : graph[v]) {       //edges v->u
            if(D[u] > D[v] + (d + BF[v] - BF[u])) {
                D[u] = D[v] + (d + BF[v] - BF[u]);
                q.push({u, D[u]});
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        std::cout << std::setw(12) << std::setfill(' ') << D[i] + BF[i] - BF[s];
    }
    std::cout << "\n";
}

//wypisuj osobno kazda linijke dijkstry nie kumuluj tego
//algp johnsona
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q;
    std::cin >> q;

    while(q--) {
        int n;
        std::cin >> n;
        std::vector<std::string> galaxies(n);
        std::map<std::string, int> map;
        std::vector<std::vector<edge>> graph(n + 1);
        //std::vector<std::vector<int>> weights(n, std::vector<int>(n));

        for(int i = 0; i < n; i++) {
            std::string s;
            std::cin >> s;
            galaxies[i] = s;
            map[s] = i;
            graph[n].push_back({i, 0});     //dodaje moj dodatkowy wierzcholek
        }

        int m;
        std::cin >> m;

        for(int i = 0; i < m; i++) {
            std::string a, b;
            int d;
            std::cin >> a >> b >> d;
            graph[map[a]].push_back({map[b], d});
        }

        std::vector<long long> BF(n + 1, LLONG_MAX);
        bellman_ford(BF, graph, n);

        std::cout << std::setw(12) << std::setfill(' ') << "";
        for(int i = 0; i < n; i++) {
            std::cout << std::setw(12) << std::setfill(' ') << galaxies[i];
        }
        std::cout << "\n";

        for(int i = 0; i < n; i++) {
            std::cout << std::setw(12) << std::setfill(' ') << galaxies[i];
            dijkstra(i, BF, graph, n);
        }
    }


    return 0;
}
