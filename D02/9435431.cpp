#include <iostream>
#include <algorithm>
#include <vector>

struct rest {
    int pos;
    int val;
};

int main() {
    int q;
    rest *places;
    long *dp;
    int *last;
    int *prev;

    std::cin >> q;

    while(q--) {
        int n, d;
        std::cin >> n >> d;
        places = new rest[n];
        dp = new long[n + 1];
        last = new int[n + 1];
        prev = new int[n];
        for(int i = 0; i < n; i++) {
            std::cin >> places[i].pos >> places[i].val;
        }

        int j = 0;
        dp[0] = 0;
        last[0] = -1;
        for(int i = 0; i < n; i++) {
            while(places[j].pos + d <= places[i].pos) j++;
            if(dp[i] < places[i].val + dp[j]) {
                dp[i + 1] = places[i].val + dp[j];
                last[i + 1] = i;
                prev[i] = last[j];
            }
            else {
                dp[i + 1] = dp[i];
                last[i + 1] = last[i];
                prev[i] = last[i];
            }
        }

        std::vector<int> ans;
        int i = n;
        while(last[i] != -1) {
            ans.push_back(last[i]);
            i = prev[last[i]] + 1;
        } 

        std::cout << dp[n] << " " << ans.size();
        for(int i = ans.size() - 1; i >= 0; i--) {
             std::cout << " " << ans[i];
        }
        std::cout << "\n";

        delete [] places;
        delete [] dp;
        delete [] last;
        delete [] prev;
        ans.clear();
    }

    return 0;
}