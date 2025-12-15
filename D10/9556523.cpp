#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

void pack(int b, std::vector<std::pair<int, int>> &dp, const std::vector<int> &items, const std::vector<int> &boxes, const std::vector<int> &powers, int n) {
    if(b == 0) {
        dp[0] = std::make_pair(0,0);
        return;
    }

    for(int i = 0; i < n; i++) {
        if(b & (powers[i]) && dp[b - (b & (powers[i]))].first == -1) pack(b - (b & (powers[i])), dp, items, boxes, powers,n);
    }

    int min_k = INT_MAX;
    int min_p = INT_MAX;

    for(int i = 0; i < n; i++) {
        if(b & (powers[i])) {
            int temp_k;
            int temp_p;
            temp_k = dp[b - (b & (powers[i]))].first;
            temp_p = dp[b - (b & (powers[i]))].second + items[i];

            if(temp_p > boxes[temp_k]) {
                temp_k++;
                while(items[i] > boxes[temp_k]) temp_k++;
                temp_p = items[i];
            }

            if(temp_k < min_k) {
                min_k = temp_k;
                min_p = temp_p;
            }
            else if(temp_k == min_k && temp_p < min_p) {
                min_k = temp_k;
                min_p = temp_p;
            } 
        }
    }

    dp[b] = std::make_pair(min_k, min_p);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q, n, m;
    std::vector<int> powers = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 
    1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 
    1048576, 2097152, 4194304, 8388608, 16777216};

    std::cin >> q;

    while(q--) {
        std::cin >> n >> m;
        std::vector<int> items(n);
        std::vector<int> boxes(m + 2);
        int subsets = powers[n];
        std::vector<std::pair<int, int>> dp(subsets, std::make_pair(-1, -1));

        for(int i = 0; i < n; i++) {
            std::cin >> items[i];
        }

        boxes[0] = 0;
        boxes[m + 1] = INT_MAX;
        for(int i = 1; i < m + 1; i++) {
            std::cin >> boxes[i];
        }

        std::sort(boxes.begin() + 1, boxes.end() - 1, std::greater<int>());
        if(m > n) {
            boxes.resize(n + 2);
            boxes[n + 1] = INT_MAX;
        }

        dp[0] = std::make_pair(0,0);

        pack(subsets - 1, dp, items, boxes, powers, n);

        if(dp[subsets - 1].first >= boxes.size() - 1) std::cout << -1 << "\n";
        else std::cout << dp[subsets - 1].first << "\n";
    }

    return 0;
}