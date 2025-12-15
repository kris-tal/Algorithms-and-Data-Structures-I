#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <utility>

int solve(int n, int M, std::vector<int> weights) {
    std::vector<long long> S(n + 1);
    std::deque<std::pair<int, int>> q;
    std::vector<int> dp(n + 1);

    S[0] = 0;
    for(int i = 1; i < n + 1; i++) S[i] = S[i - 1] + weights[n - i];

    dp[0] = 0;
    q.push_back(std::make_pair(0, 0));
    for(int i = 1; i < n + 1; i++) {
        while(!q.empty() && S[i] - S[q.front().first] > M) q.pop_front();
        dp[i] = S[i] - q.front().second;
        while(!q.empty() && q.back().second >= dp[i]) q.pop_back();
        q.push_back(std::make_pair(i, dp[i]));
    }

    return dp[n];
}

int main() {
    int t, n, M;
    fread(&t, sizeof(int), 1, stdin);
    while (t--) {
        fread(&n, sizeof(int), 1, stdin);
        fread(&M, sizeof(int), 1, stdin);
        std::vector<int> input(n);
        fread(input.data(), sizeof(int)*n, 1, stdin);
        printf("%d\n", solve(n, M, std::move(input)));
    }
}