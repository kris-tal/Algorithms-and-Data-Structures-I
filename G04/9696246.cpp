#include <iostream>
#include <climits>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iomanip>

#define ALPH 26 * 26
//#define ALPH 15               //pamietaj zeby to zmienic potem blagam

bool dfs(int v, std::vector<std::vector<int>> &graph, std::vector<int> &color) {
    color[v] = 1;

    for(auto u : graph[v]) {
        if(color[u] == 1) return true;
        if(color[u] == 0) {
            if(dfs(u, graph, color) == true) return true;
        }
    }

    color[v] = 2;
    return false;
}

bool cycle_checker(int N, std::vector<std::vector<int>> &graph) {
    std::vector<int> color(N + 1, 0);
    return dfs(N, graph, color);        //wystarczy jeden bo puszczam z tego polaczonego ze wszystkimi
}

//bellman-ford
bool relax(int u, int v, long double weight, std::vector<long double> &D) {
    if(D[v] > D[u] + weight) {
        D[v] = std::max((long double)D[u] + weight, (long double)LLONG_MIN);
        return true;
    }
    return false;
}

bool bellman_ford(long double avg, std::vector<std::vector<int>> &graph, const std::vector<std::vector<int>> &weights, int N) {
    std::vector<long double> D(N + 1, LLONG_MAX);
    D[N] = 0;           //startujemy z N+1

    bool relaxed = true;
    for(int i = 0; i < N + 1 && relaxed; i++) {
        relaxed = false;
        for(int u = N; u >= 0; u--) {    //to tak jakby e : edges
            for(auto v : graph[u]) {
                if(relax(u, v, avg - (long double)weights[u][v], D)) relaxed = true;
            }
        }
    }

    return relaxed;
}

long double binsearch(long double l, long double r, std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &weights, int N) {
    double p = 0.00001;
    while (r - l > p) {
        long double mid = (l + r) / 2.0;
        if (bellman_ford(mid, graph, weights, N)) l = mid;
        else r = mid;
    }
    return l;
}

int main() {
    int q;
    std::cin >> q;

    while(q--) {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int n;
        std::cin >> n;

        std::unordered_map<std::string, long long> map;
        std::vector<std::vector<int>> weights(ALPH + 1, std::vector<int>(ALPH + 1, 0));

        long double max_len = 0;

        for(int i = 0; i < n; i++) {
            std::string s;
            std::cin >> s;
            std::string beg = s.substr(0, 2);
            std::string  end = s.substr(s.size() - 2, 2);

            if(map.find(beg) == map.end()) map[beg] = map.size();
            if(map.find(end) == map.end()) map[end] = map.size();
            weights[map[beg]][map[end]] = std::max(weights[map[beg]][map[end]], (int)s.size());         //tym razem skierowany
            max_len = std::max(max_len, (long double)s.size());
        }

        int N = map.size();
        std::vector<std::vector<int>> vert(N + 1);

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(weights[i][j] != 0) vert[i].push_back(j);
            }
        }

        for(int i = 0; i < N; i++) {            //wierzch polaczony ze wszystkimi (nie tworzy cyklu bo nie ma wchodzacych wiec nie powinien zmieniac wyniku)
            vert[N].push_back(i);
        }

        if(!cycle_checker(N, vert)) std::cout << "NIE\n";
        else {
            std::cout << std::fixed << std::setprecision(4) << std::round(10000.0 * binsearch(0.0, (long double)max_len, vert, weights, N)) / 10000.0 << "\n";
        }
    }

    return 0;
}
