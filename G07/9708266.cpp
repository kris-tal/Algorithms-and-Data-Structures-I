#include <iostream>
#include <vector>
#include <map>

#define CAP 10000

struct edge {
    int beg;
    int end;
    int len;
    bool in_opt = false;
};

struct edge_idx {
    int beg_idx;
    int end_idx;
    int vert;
};

struct DSU {
    DSU *p = this;
    int size = 1;       //rozmiar zbioru
    DSU() = default;
    DSU(const DSU &) = delete;
    DSU &operator = (const DSU &) = delete; 
};

DSU *find(DSU* v) {
    if(v != v->p)  v->p = find(v->p);
    return v->p;  
}

bool join(DSU *x, DSU *y) {
    x = find(x);
    y = find(y);        //czyli wyciagnelismy reprezentantow
    if(x == y) return false;        //nie sa ci sami czyli chcemy teraz doczepic mniejszego do wiekszego
    if(x->size < y->size) std::swap(x, y);
    y->p = x;
    x->size += y->size;
    return true;
}

void span(std::vector<edge> &edges, std::vector<std::vector<edge*>> &sets, int n) {
    std::vector<DSU> trees(n);      //nie mozemy resizowac tego vectora

    for(int i = 0; i < CAP; i++) {
        if(sets[i].size() == 0) continue;
        std::vector<int> working_edges;

        for(auto e : sets[i]) {
            DSU* dsu_beg = find(&trees[e->beg]);
            DSU* dsu_end = find(&trees[e->end]);

            if(dsu_beg != dsu_end) {
                e->in_opt = true;
            }
        }

        for(auto e : sets[i]) {
            if(!e->in_opt) continue;
            DSU* dsu_beg = find(&trees[e->beg]);
            DSU* dsu_end = find(&trees[e->end]);
            if(dsu_beg != dsu_end) {
                join(dsu_beg, dsu_end);
            }
        }
    }
}

int main() {
    int q;
    std::cin >> q;
    
    while(q--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<edge> edges(m);
        std::vector<std::vector<edge*>> sets(CAP + 1);

        for(int i = 0; i < m; i++) {
            int a, b, l;
            std::cin >> a >> b >> l;
            a--; b--;
            edges[i] = {a, b, l};
            sets[l].push_back(&edges[i]);
        }

        span(edges, sets, n);

        for(auto e : edges) {
            if(e.in_opt) std::cout << "TAK\n";
            else std::cout << "NIE\n";
        }
    }

    return 0;
}