#include <iostream>
#include <algorithm>

int main() {
    int q;
    int **dp;

    std::cin >> q;

    while(q--) {
        std::string a, b;
        std::cin >> a >> b;
        int SIZE_A = a.size() + 1;
        int SIZE_B = b.size() + 1;

        dp = new int*[SIZE_A];
        for(int i = 0; i < SIZE_A; i++) {
            dp[i] = new int[SIZE_B];
        }

        for(int i = 0; i < SIZE_A; i++) {     //column base
            dp[i][0] = 0;
        }

        for(int j = 0; j < SIZE_B; j++) {     //row base
            dp[0][j] = 0;
        }
        
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < b.size(); j++) {
                if(a[i] == b[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                }
                else {
                    dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }

        std::cout << dp[a.size()][b.size()] << "\n";

        std::string ans = "";

        int i = a.size();
        int j = b.size();

        while(i > 0 && j > 0) {
            if(dp[i - 1][j - 1] == dp[i][j] - 1 && a[i - 1] == b[j - 1]) {
                ans = b[j - 1] + ans;
                i--;
                j--;
            }
            else {
                if(dp[i - 1][j] > dp[i][j - 1]) i--;
                else j--;
            }
        }

        std::cout << ans << "\n";

        for(int i = 0; i < SIZE_A; i++) {
            delete [] dp[i];
        }
        delete [] dp;
    }

    return 0;
}