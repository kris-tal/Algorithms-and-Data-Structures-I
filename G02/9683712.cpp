#include <iostream>
#include <vector>
#include <climits>

void preorder(int v, std::vector<bool> &visited, const std::vector<std::vector<int>> &graph, std::vector<int> &pre, int &counter) {
    visited[v] = true;
    pre[v] = counter;
    counter++;

    for(auto u : graph[v]) {
        if(!visited[u]) preorder(u, visited, graph, pre, counter);
    }
}

void dfs(int v, int p, std::vector<bool> &visited, const std::vector<std::vector<int>> &graph, const std::vector<int> &pre, std::vector<int> &low, std::vector<bool> &art) {
    visited[v] = true;
    low[v] = pre[v];
    int children = 0;

    for(auto u : graph[v]) {
        if(u == p) continue;
        if(visited[u]) low[v] = std::min(low[v], pre[u]);
        else {
            dfs(u, v, visited, graph, pre, low, art);
            low[v] = std::min(low[v], low[u]);
            if(low[u] >= pre[v] && p != -1) art[v] = true;
            children++;
        }
    }
    if(p == -1 && children > 1) art[v] = true;
}

bool check(const std::vector<bool> &art) {
    for(auto v : art) {
        if(v) return false;
    }
    return true;
}

int new_col(const int &a, const int &b) {
    for(int i = 0; i < 3; i++) {
        if(a == i || b == i) continue;
        return i;
    }
}

void color(int v, int p, std::vector<bool> &visited, const std::vector<std::vector<int>> &graph, const std::vector<int> &pre, const std::vector<int> &low, std::vector<int> &colors) {
    visited[v] = true;
    int min_back = INT_MAX;
    
    for(auto u : graph[v]) {
        if(u != p && visited[u]) min_back = std::min(min_back, u);
    }

    if(min_back == INT_MAX) min_back = 0;

    if(p == -1) colors[v] = 0;
    else colors[v] = new_col(colors[p], colors[min_back]);

    for(auto u : graph[v]) {
        if(u == p) continue;
        if(visited[u]) min_back = u;
        else {
            color(u, v, visited, graph, pre, low, colors);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    while(q--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> graph(n);

        for(int i = 0; i < m; i++) {
            int a, b;
            std::cin >> a >> b;
            a--;
            b--;

            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        std::vector<bool> visited(n, false);
        std::vector<int> pre(n);
        int counter = 0;
        
        preorder(0, visited, graph, pre, counter);

        std::vector<int> low(n);
        std::vector<bool> art(n, false);

        int connected = true;
        for(auto v : visited) {
            if(v == false) connected = false;
            v = false;
        }

        dfs(0, -1, visited, graph, pre, low, art);

        std::vector<int> colors(n, -1);
        for(auto v : visited) v = false;

        if(connected && check(art)) {
            std::cout << "TAK\n";
            color(0, -1, visited, graph, pre, low, colors);
            for(auto c : colors) std::cout << c + 1 << " ";
            std::cout << "\n";
        }
        else std::cout << "NIE\n";
    }

    return 0;
}