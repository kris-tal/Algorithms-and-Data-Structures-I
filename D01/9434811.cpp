#include <iostream>

int main() {
    int q;
    int *holes;
    int *dp;

    std::cin >> q;

    while(q--) {
        int n, m;
        std::cin >> n >> m;
        holes = new int[n];
        dp = new int[n];
        for(int i = 0; i < n; i++) {
            char c;
            std::cin >> c;
            holes[i] = c - '0';
        }

        dp[0] = 1;
        for(int i = 1; i < n; i++) {
            int sum = 0;
            for(int j = 1; j <= 6; j++) {
                if(i - j >= 0) sum = (sum + dp[i - j]) % m;
            }
            dp[i] = holes[i] * sum;
        }

        std::cout << dp[n - 1] << "\n";

        delete [] holes;
        delete [] dp;
    }

    return 0;
}