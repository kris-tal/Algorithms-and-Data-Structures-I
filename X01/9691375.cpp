#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    std::random_device rd;
    std::mt19937_64 myRandom(rd());

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> nums(n);
    std::vector<unsigned long long> map(m + 3, -1);
    std::unordered_map<unsigned long long, unsigned long long> prefixes;
    std::vector<unsigned long long> pref(n, -1);

    for(int i = 0; i < n; i++) {
        std::cin >> nums[i];
        if(map[nums[i]] == -1) map[nums[i]] = myRandom();
        pref[i] = map[nums[i]];
    }

    int max = 0;
    prefixes[pref[0]] = 0;
    for(int i = 1; i < n; i++) {
        pref[i] ^= pref[i - 1];
        if(prefixes.find(pref[i]) == prefixes.end()) prefixes[pref[i]] = i;
        else max = std::max((unsigned long long)max, i - prefixes[pref[i]]);
    }

    std::cout << max << "\n";
   
    return 0;
}