#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

int my_lg(int n) {
    if (n == 0) return 0;
    int power = 1;
    while (power * 2 <= n) {
        power *= 2;
    }
    return power;
}

typedef std::array<int, 8> S_8;

S_8 operator+(const S_8& a, const S_8& b) {
    S_8 result;
    for(int i = 0; i < 8; i++) {
        result[i] = b[a[i]];
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, const S_8& s8) {
    for(int i = 0; i < 8; i++) {
        stream << s8[i] + 1 << " ";
    }
    std::cout << "\n";
    return stream;
}

std::istream& operator>>(std::istream& stream, S_8& s8) {
    for(int i = 0; i < 8; i++) {
        stream >> s8[i];
        s8[i]--;
    }
    return stream;
}

struct node {
    std::vector<int> adj;
    S_8 perm;
    int enter;
    int exit;
};

S_8 inverse(const S_8 &perm) {
    S_8 result;
    for(int i = 0; i < 8; i++) {
        result[perm[i]] = i;
    }
    return result;
}

void dfs(int v, int p, std::vector<S_8> &s_tree, std::vector<node> &tree, int &idx, int N) {
    if(v != 0){
        s_tree[idx] = tree[v].perm;
        idx++;
        tree[v].enter = idx - N;
    }

    for(auto u : tree[v].adj) {
        if(u != p)
            dfs(u, v, s_tree, tree, idx, N);
    }

    if(v != 0){
        s_tree[idx] = inverse(tree[v].perm);
        tree[v].exit = idx - N;
        idx++;
    }
}

void build_tree(std::vector<S_8> &s_tree, int N, int n) {
    s_tree[0] = {0, 1, 2, 3, 4, 5, 6, 7};
    for(int i = n + N; i < 2 * N; i++) {
        s_tree[i] = {0, 1, 2, 3, 4, 5, 6, 7};
    }
    for(int i = N - 1; i >= 1; i--) {
        s_tree[i] = s_tree[2 * i] + s_tree[2 * i + 1];
    }
}

void update(int i, S_8 new_perm, std::vector<S_8> &s_tree, int N) {
    i += N;
    s_tree[i] = new_perm;
    while(i > 1) {
        i /= 2;
        s_tree[i] = s_tree[2 * i] + s_tree[2 * i + 1];
    }
}
//query<p, q)
S_8 query(int l, int r, std::vector<S_8> &s_tree, int N) {
    l += N;
    r += N;
    S_8 l_perm = s_tree[l];
    S_8 r_perm = {0, 1, 2, 3, 4, 5, 6, 7};
    while(l / 2 != r / 2) {
        if(l % 2 == 0) l_perm = l_perm + s_tree[l + 1];
        if(r % 2 == 1) r_perm = s_tree[r - 1] + r_perm;
        l /= 2;
        r /= 2;
    }
    return l_perm + r_perm;
}

int main() {
    int z;
    std::cin >> z;

    while(z--) {
        int n;
        std::cin >> n;
        std::vector<node> routers(n);
        int edges = (n - 1) * 2;
        //int N = 1 << my_lg(edges);
        int N = 1 << std::__lg(edges);
        if(N != edges) N = N << 1;

        for(int i = 1; i < n; i++) {
            int parent;
            std::cin >> parent;
            parent--;
            routers[parent].adj.push_back(i);
            routers[i].adj.push_back(parent);
            std::cin >> routers[i].perm;
            routers[i].enter = -1;
        }


        std::vector<S_8> s_tree(2 * N);

        int idx = N;
        dfs(0, -1, s_tree, routers, idx, N);
        build_tree(s_tree, N, edges);
        routers[0].enter = 0;
        int q;
        std::cin >> q;
        while(q--) {
            int com;
            std::cin >> com;
            if(com == 1) {
                int v;
                S_8 new_perm;
                std::cin >> v >> new_perm;
                v--;
                update(routers[v].enter - 1, new_perm, s_tree, N);
                update(routers[v].exit, inverse(new_perm), s_tree, N);
            }
            else {
                int u, v;
                std::cin >> u >> v;
                u--;
                v--;
                if(u == v) std::cout << "1 2 3 4 5 6 7 8\n";
                else {
                    if(routers[u].enter > routers[v].enter) {
                        std::swap(u, v);
                        std::cout << inverse(query(routers[u].enter, routers[v].enter, s_tree, N));
                    }
                    else std::cout << query(routers[u].enter, routers[v].enter, s_tree, N);
                }
            }
        }
    }

    return 0;
}