#include <iostream>
#include <vector>

struct node {
    bool set;
    int dp;
    bool free;
    bool taken;
    std::vector<int> adj;
};

void DFS(int v, std::vector<bool> &visited, std::vector<bool> &is_child, std::vector<node> &tree) {
    visited[v] = true;

    for(int u : tree[v].adj) {
        if(!visited[u]) DFS(u, visited, is_child, tree);
    }
    
    tree[v].dp = 0;
    int free = tree[v].set;
    for(int u : tree[v].adj) {
        free += tree[u].free * is_child[u];
        tree[v].dp += tree[u].dp * is_child[u];
    }
    if(free >= 2) {
        tree[v].dp++;
        tree[v].free = false;
    }
    else {
        tree[v].free = free;
    }

    is_child[v] = true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q, n, w;
    std::cin >> q;

    while(q--) {
        std::cin >> n;
        std::vector<node> tree(n);
        for(int i = 0; i < n; i++) {
            tree[i].taken = false;
            tree[i].set = false;
        }
        for(int i = 0; i < n - 1; i++) {
            int a, b;
            std::cin >> a >> b;
            tree[a - 1].adj.push_back(b - 1);
            tree[b - 1].adj.push_back(a - 1);
        }
        std::cin >> w;
        for(int i = 0; i < w; i++) {
            int a;
            std::cin >> a;
            tree[a - 1].set = true;
        }

        std::vector<bool> visited(n, false);
        std::vector<bool> is_child(n, false);
        DFS(0, visited, is_child, tree);

        std::cout << tree[0].dp << "\n";
    }

    return 0;
}