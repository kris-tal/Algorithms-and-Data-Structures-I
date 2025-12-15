#include <iostream>
#include <vector>
#include <stack>

int normalize(const int &a) {
    if(a < 0) return ((-a) - 1) * 2 + 1;
    else return (a - 1) * 2;
}

int neg(const int &a) {
    if(a % 2 == 0) return a + 1;
    else return a - 1;
}

void first_dfs(int v, std::vector<std::vector<int>> &graph, std::vector<bool> &visited, std::stack<int> &s) {
    visited[v] = true;
    for(auto u : graph[v]) {
        if(!visited[u]) first_dfs(u, graph, visited, s);
    }

    s.push(v);
}

void second_dfs(int v, int layer, std::vector<std::vector<int>> &graph, std::vector<int> &topo) {
    topo[v] = layer;
    for(auto u : graph[v]) {
        if(topo[u] == -1) second_dfs(u, layer, graph, topo);
    }
}

bool check(const std::vector<int> &topo, std::vector<bool> &eval, int n) {
    for(int i = 0; i < n; i++) {
        if(topo[2 * i] == topo[2 * i + 1]) return false;
        if(topo[2 * i] > topo[2 * i + 1]) eval[i] = true;
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    while(q--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> graph(2 * n);
        std::vector<std::vector<int>> rev_graph(2 * n);
        
        for(int i = 0; i < m; i++) {
            int a, b;
            std::cin >> a >> b;
            a = normalize(a);
            b = normalize(b);

            graph[neg(a)].push_back(b);
            graph[neg(b)].push_back(a);

            rev_graph[b].push_back(neg(a));
            rev_graph[a].push_back(neg(b));
        }

        //kosaraju

        std::stack<int> s;
        std::vector<bool> visited(2 * n, false);

        for(int i = 0; i < 2 * n; i++) {
            if(!visited[i]) first_dfs(i, graph, visited, s);
        }

        std::vector<int> topo(2 * n, -1);

        int layer = 0;
        while(!s.empty()) {
            int v = s.top();
            if(topo[v] == -1) {
                second_dfs(v, layer, rev_graph, topo);
                layer++;
            }
            s.pop();
        }

        std::vector<bool> eval(n, false);
        if(check(topo, eval, n)) {
            std::cout << "TAK\n";
            for(auto val : eval) std::cout << val << " ";
            std::cout << "\n";
        }
        else std::cout << "NIE\n";

    }

    return 0;
}