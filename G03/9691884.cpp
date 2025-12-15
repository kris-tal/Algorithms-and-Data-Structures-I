#include <iostream>
#include <iomanip>
#include <climits>
#include <vector>
#include <unordered_map>

int main() {
    int q;
    std::cin >> q;

    while(q--) {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int n, m;
        std::cin >> n;
        std::vector<std::string> cities(n);
        std::unordered_map<std::string, long long> map(n);

        for(int i = 0; i < n; i++) {
            std::string s;
            std::cin >> s;
            cities[i] = s;
            map[s] = i;
        }

        std::cin >> m;
        std::vector<std::vector<long long>> G(n, std::vector<long long>(n, INT_MAX));

        for(int i = 0; i < m; i++) {
            std::string a, b;
            int d;
            std::cin >> a >> b >> d;
            G[map[a]][map[b]] = d;
            G[map[b]][map[a]] = d;
        }

        for(int i = 0; i < n; i++) {
            G[i][i] = 0;
        }

        std::vector<std::vector<std::vector<long long>>> D(2);
        D[0] = D[1] = G;

        for(int k = 0; k < n; k++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(D[0][i][j] > D[0][i][k] + D[0][k][j]) {
                        D[1][i][j] = D[0][i][k] + D[0][k][j];
                    }
                }
            }
            D[0] = D[1];
        }

        std::cout << std::setw(12) << std::setfill(' ') << "";
        for(int i = 0; i < n; i++) {
            std::cout << std::setw(12) << std::setfill(' ') << cities[i];
        }
        std::cout << "\n";

        for(int i = 0; i < n; i++) {
            std::cout << std::setw(12) << std::setfill(' ') << cities[i];
            for(int j = 0; j < n; j++) {
               std::cout << std::setw(12) << std::setfill(' ') << D[1][i][j];
            }
            std::cout << "\n";
        }

    }

    return 0;
}