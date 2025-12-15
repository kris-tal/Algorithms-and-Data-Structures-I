#include <iostream>
#include <algorithm>
#include <vector>

struct item {
    int weight;
    int value;
};

void dynamic(int start, int end, item *items, int B, int *dp) {
    for(int i = 0; i < B; i++) dp[i] = 0;

    for(int i = 0; i < B; i++) dp[i] = 0;
    for(int i = start; i < end; i++) {
        for(int j = B - 1; j >= 0; j--) {
            if(items[i].weight > j) continue;
            dp[j] = std::max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }
}

int dac(int start, int end, item *items, int b, std::vector<int> &taken) {
    if(b == 0 || start == end) return 0;
    int *dp1 = new int[b + 1];
    int *dp2 = new int[b + 1];

    dynamic(start, (start + end + 1) / 2, items, b + 1, dp1);
    if(end - start ==  1) { 
        for(int i = 0; i < b + 1; i++) dp2[i] = 0;
    }
    else dynamic((start + end + 1) / 2, end, items, b + 1, dp2);

    int max = 0;
    int vol;
    for(int i = 0; i < b + 1; i++) {
        if(dp1[i] + dp2[b + 1 - 1 - i] >= max) {
            max = dp1[i] + dp2[b + 1 - 1 - i];
            vol = i;
        }
    }

    delete [] dp1;
    delete [] dp2;
    if(end - start == 1 && max > 0) taken.push_back(start);
    if(end - start >  1) dac(start, (start + end + 1) / 2, items, vol, taken) + dac((start + end + 1) / 2, end, items, b - vol, taken);
    return max;
}

int main() {
    int q;
    int n, b;
    std::vector<int> ans;

    std::cin >> q;

    while(q--) {
        std::cin >> n >> b;
        item items[n];

        for(int i = 0; i < n; i++) {
            std::cin >> items[i].weight >> items[i].value;
        }

        std::cout << dac(0, n, items, b, ans) << " " << ans.size() << "\n";

        for(int i = 0; i < ans.size(); i++) std::cout << ans[i] + 1 << " ";
        std::cout << "\n";

        ans.clear();
    }

    return 0;
}