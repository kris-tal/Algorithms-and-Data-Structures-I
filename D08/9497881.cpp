#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

void lis(std::vector<int> &heights, int n) {
    std::vector<int> dp(n + 1, 0);
    std::vector<int> prev(n + 1, -1);
    int L = 0;

    for(int i = 0; i < n; i++) {
        int k = std::lower_bound(dp.begin() + 1, dp.begin() + L + 1 , i, [&](int idx, int _){return heights[idx] < heights[i]; }) - dp.begin();
        prev[i] = dp[k - 1];
        dp[k] = i;

        L = std::max(L, k);
    }
    

    
    std::vector<int> ans;
    int j = n - 1;
    int idx = dp[L];
    for(int i = 0; i < L; i++) {
        while(j > idx) {
            ans.push_back(j + 1);
            j--;
        }
        j--;
        idx = prev[idx];
    }
    while(j >= 0) {
        ans.push_back(j + 1);
        j--;
    }

    std::cout <<  n - L << "\n";
    for(int i = ans.size() - 1; i >= 0; i--) {
        std::cout << ans[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int q, n;
    std::cin >> q;
    
    while(q--) {
        std::cin >> n;
        std::vector<int> heights(n);
        
        for(int i = 0; i < n; i++) {
            std::cin >> heights[i];
        }

        lis(heights, n);
    }

    return 0;
}