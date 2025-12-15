#include <iostream>
#include <vector>
#include <algorithm>

struct node {
    int val;
    int mod;
    operator int() const {
        return val + mod;
    }
};

void update(int p, int q, int val, int N, std::vector<node> &s_tree) {
    p += N - 1;
    q += N - 1;

    if(q < p) return;
    s_tree[p].mod += val;
    if(p < q) {
        s_tree[q].mod += val;

        while(p / 2 != q / 2) {
            if(p % 2 == 0) s_tree[p + 1].mod += val;
            if(q % 2 == 1) s_tree[q - 1].mod += val;
            p /= 2;
            q /= 2;
            s_tree[p].val = std::max(s_tree[2 * p], s_tree[2 * p + 1]);
            s_tree[q].val = std::max(s_tree[2 * q], s_tree[2 * q + 1]);
        }
    }
    while(p /= 2) {
        s_tree[p].val = std::max(s_tree[2 * p], s_tree[2 * p + 1]);
    }
}

int query(int p, int q, int N, std::vector<node> &s_tree) {
    p += N - 1;
    q += N - 1;

    int p_res = s_tree[p];
    if(p < q) {
        int q_res = s_tree[q];
        while(p / 2 != q / 2) {
            if(p % 2 == 0) p_res = std::max(p_res, (int)s_tree[p + 1]);
            if(q % 2 == 1) q_res = std::max(q_res, (int)s_tree[q - 1]);
            p /= 2;
            q /= 2;
            p_res += s_tree[p].mod;
            q_res += s_tree[q].mod;
        }
        p_res = std::max(p_res, q_res);
    }
    while(p /= 2) {
        p_res += s_tree[p].mod;
    }
    return p_res;
}

int main() {
    int z;
    std::cin >> z;

    while(z--) {
        int n, m, q;
        std::cin >> n >> m >> q;
        n--;    //bo patrze na odcinki

        int N = 1 << std::__lg(n);
        if(N != n) N = N << 1;
        
        std::vector<node> segment_tree(2 * N);
        for(int i = 0; i < 2 * N; i++) {
            segment_tree[i].val = 0;
            segment_tree[i].mod = 0;
        }
        for(int i = 0; i < q; i++) {
            int p, k, l;
            std::cin >> p >> k >> l;
            if(m - query(p, k - 1, N, segment_tree) >= l) {
                update(p, k - 1, l, N, segment_tree);
                std::cout << "T\n";
            }
            else std::cout << "N\n";
        }

    }

    return 0;
}
