#include <iostream>
#include <algorithm>

struct item {
    int weight;
    int value;
};

int main() {
    int q;
    int n, b;
    std::cin >> q;

    while(q--) {
        std::cin >> n >> b;
        item items[n];
        int dp[b + 1];

        for(int i = 0; i < n; i++) {                            //wczytujemy itemy
            std::cin >> items[i].weight >> items[i].value;
        }

        for(int i = 0; i < b + 1; i++) dp[i] = 0;    //zerujemy dla pustego plecaka
        for(int i = 0; i < n; i++) {
            for(int j = b; j >= 0; j--) {
                if(items[i].weight > j) continue;
                dp[j] = std::max(dp[j], dp[j - items[i].weight] + items[i].value);
            }
        }

        std::cout << dp[b] << "\n";

    }

    return 0;
}