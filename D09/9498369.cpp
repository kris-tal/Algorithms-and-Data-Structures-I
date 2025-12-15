#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

struct node {
    int val;
    long long w;
    long long r;
    bool taken;
    std::vector<int> adj;
};

void DFS(int v, std::vector<bool> &visited, std::vector<bool> &is_child, std::vector<node> &tree) {
    visited[v] = true;

    for(int u : tree[v].adj) {
        if(!visited[u]) DFS(u, visited, is_child, tree);
    }

    tree[v].w = tree[v].val;
    for(int u : tree[v].adj) tree[v].w += tree[u].r * is_child[u];
    tree[v].r = 0;
    for(int u : tree[v].adj) tree[v].r += tree[u].w * is_child[u];
    tree[v].r = std::min(tree[v].r, tree[v].w);


    is_child[v] = true;
}

void reconstruct(int v, std::vector<bool> &visited, std::vector<node> &tree, bool parent_taken) {
    visited[v] = true;

    if(!parent_taken) tree[v].taken = true;
    else if(tree[v].w <= tree[v].r) tree[v].taken = true;

    for(int u : tree[v].adj) {
        if(!visited[u]) reconstruct(u, visited, tree, tree[v].taken);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q, n;
    std::cin >> q;

    while(q--) {
        std::cin >> n;
        std::vector<node> tree(n);
        for(int i = 0; i < n; i++) {
            std::cin >> tree[i].val;
            tree[i].taken = false;
        }
        for(int i = 0; i < n - 1; i++) {
            int a, b;
            std::cin >> a >> b;
            tree[a - 1].adj.push_back(b - 1);
            tree[b - 1].adj.push_back(a - 1);
        }

        std::vector<bool> visited(n, false);
        std::vector<bool> is_child(n, false);
        DFS(0, visited, is_child, tree);

        std::cout << tree[0].r << "\n";

        for(int i = 0; i < n; i++) visited[i] = false;
        reconstruct(0, visited, tree, 1);

        for(int i = 0; i < n; i++) {
            std::cout << tree[i].taken;
        }
        std::cout << "\n";

    }

    return 0;
}