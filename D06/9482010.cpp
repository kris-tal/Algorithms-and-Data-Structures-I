#include <iostream>
#include <vector>
#include <algorithm>

struct vertex {
    std::vector<int> adj;
    int val;
};

void toposort(int v, bool* visited, vertex *vert) {
    visited[v] = true;

    for(int i = 0; i < vert[v].adj.size(); i++) {
        if(!visited[vert[v].adj[i]]) toposort(vert[v].adj[i], visited, vert);
    }

    int max = 0;
    for(int i = 0; i < vert[v].adj.size(); i++) {
        max = std::max(max, vert[vert[v].adj[i]].val);
    }

    vert[v].val = max + 1;
}

int main() {
    int q;
    std::cin >> q;

    vertex *vert;
    vertex *rev_vert;
    bool *visited;

    while(q--) {
        int n, m;
        std::cin >> n >> m;
        vert = new vertex[n];
        for(int i = 0; i < n; i++) vert[i].val = 0;
        rev_vert = new vertex[n];
        for(int i = 0; i < n; i++) rev_vert[i].val = 0;

        for(int i = 0; i < m; i++) {
            int a, b;
            std::cin >> a >> b;
            vert[a - 1].adj.push_back(b - 1);
            rev_vert[b - 1].adj.push_back(a - 1);
        }


        visited = new bool[n];
        for(int i = 0; i < n; i++) visited[i] = false;

        for(int i = 0; i < n; i++) {
            if(!visited[i]) toposort(i, visited, vert);
        }
    
        for(int i = 0; i < n; i++) visited[i] = false;

        for(int i = 0; i < n; i++) {
            if(!visited[i]) toposort(i, visited, rev_vert);
        }
        
        for(int i = 0; i < n; i++) {
            std::cout << vert[i].val + rev_vert[i].val - 1 << " ";
        }
        std::cout << "\n";

        delete [] vert;
        delete [] rev_vert;
        delete [] visited;
    }



    return 0;
}