#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct cmd {
    int id;
    int next;
};

struct cmp {
    bool operator()(const cmd& a, const cmd& b) {
        return a.next < b.next; 
    }
};

int run(std::vector<cmd> cmds, int k, int n) {
    std::priority_queue<cmd, std::vector<cmd>, cmp> cache;
    std::vector<bool> is_cached(n, false);

    int counter = 0;
    int diff = 0;

    for(cmd c : cmds) {
        if(is_cached[c.id]) cache.push(c);
        else {
            if(diff < k) {
                cache.push(c);
                counter++;
                is_cached[c.id] = true;
            }
            else {
                is_cached[cache.top().id] = false;
                cache.pop();
                diff--;
                cache.push(c);
                counter++;
                is_cached[c.id] = true;
            }
            diff++;
        }
    }
    return counter;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    while(q--) {
        int k, n, m;
        std::cin >> k >> n >> m;
        std::vector<cmd> cmds(m);
        std::vector<int> last(n, -1); 

        for(int i = 0; i < m; i++) {
            int com;
            std::cin >> com;
            com--;
            cmds[i].id = com;
            if(last[com] != -1) cmds[last[com]].next = i; 
            last[com] = i;
        }
        
        for(int i : last) {
            if(i != -1) cmds[i].next = m + 1;
        }

        std::cout << run(cmds, k, n) << "\n";
    }

    return 0;
}