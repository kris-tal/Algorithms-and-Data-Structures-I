#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    int q;
    std::cin >> q;

    while(q--) {
        int n, T;
        std::cin >> n >> T;
        std::priority_queue<int, std::vector<int>, std::greater<int>> h;
        for(int i = 0; i < n; i++) {
            int t;
            std::cin >> t;
            h.push(t);
        }
        while(h.size() > 1) {
            int t1, t2;
            t1 = h.top();
            h.pop();
            t2 = h.top();
            h.pop();
            h.push(T + std::max(t1, t2));
        }
        std::cout << h.top() << "\n";
        h.pop();
    }

    return 0;
}