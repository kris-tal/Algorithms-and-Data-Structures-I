#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>
#include <queue>

struct cmp {
    bool operator()(const int& a, const int& b) {
        return a > b; 
    }
};

bool check(std::vector<std::pair<int, int>> set, std::vector<std::pair<int, int>> &times) {
    int k = set.size();

    std::sort(set.begin(), set.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b){
        return a.first < b.first; });

    std::priority_queue<int, std::vector<int>, cmp> h;
    int j = 0;
    int i = set[0].first;
    while(j < k || !h.empty()) {        //
        while(j <  k && set[j].first == i) {
            h.push({set[j].second});
            j++;
        }

        if(!h.empty()) {
            if(i < h.top()) h.pop();
            else return false;
        }
        else if(j < k) i = set[j].first - 1;
        i++;
    }

    if(!h.empty()) return false;
    return true;
}

int shopping(std::vector<std::pair<int, int>> &values, std::vector<std::pair<int, int>> &times) {
    std::vector<std::pair<int, int>> set;
    int ans = 0;    ////
    for(auto v : values) {
        set.push_back({times[v.first].first, times[v.first].second});
        if(!check(set, times)) set.pop_back();
        else ans += v.second;
    }

    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q;
    std::cin >> q;

    while(q--) {
        int n;
        std::cin >> n;
        if(n == 0) {
            std::cout << "0\n";
            continue;
        }
        std::vector<std::pair<int, int>> values(n);
        std::vector<std::pair<int, int>> times(n);
        
        for(int i = 0; i < n; i++) {
            int op, cl, val;
            std::cin >> op >> cl >> val;
            values[i] = {i, val};
            times[i] = {op, cl};
        }

        std::sort(values.begin(), values.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b){
                    return a.second > b.second; });

        std::cout << shopping(values, times) << "\n";
    }

    return 0;
}