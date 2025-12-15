#include <iostream>
#include <algorithm>
#include <climits>

void print_swiszcz(int i, int j, int **sw, int *cuts) {
    if(sw[i][j] == -1) return;
    std::cout << cuts[sw[i][j] + j] << " ";
    print_swiszcz(i - sw[i][j], sw[i][j] + j, sw, cuts);
    print_swiszcz(sw[i][j], j, sw, cuts);
}

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);
    int q;
    int d, n;
    std::cin >> q;
    int *cuts;
    int **swiszcz;

    while(q--) {
        std::cin >> d >> n;
        int N = n + 1;              //liczba przeciec lacznie z koncami
        cuts = new int[N + 1];
        swiszcz = new int*[N + 1];
        for(int i = 0; i < N + 1; i++) swiszcz[i] = new int[N + 1];
        for(int i = 0; i < N + 1; i++) swiszcz[1][i] = -1;

        long long dp[N + 1][N + 1]; 
        for(int i = 0; i < N + 1; i++) dp[1][i] = 0;

        cuts[0] = 0;
        cuts[n + 1] = d;
        for(int i = 1; i < n + 1; i++) {
            std::cin >> cuts[i];
        }

        std::sort(cuts, cuts + N + 1);

        for(int i = 2; i < N + 1; i++) {
            for(int j = 0; j < N + 1 - i; j++) {
                long long min = LLONG_MAX;
                int min_idx;
                for(int k = 1; k < i; k++) {
                    long long temp = dp[k][j] + dp[i - k][j + k] + std::max(cuts[j + k] - cuts[j], cuts[j + i] - cuts[j + k]);
                    if(temp < min) {
                        min = temp;
                        min_idx = k;
                    }
                }
                swiszcz[i][j]= min_idx;
                dp[i][j] = min;
            }
        }

        std::cout << dp[n + 1][0] << "\n";
        print_swiszcz(n + 1, 0, swiszcz,  cuts);
        std::cout << "\n";

        delete [] cuts;
        for(int i = 0; i < N + 1; i++) delete [] swiszcz[i];
        delete [] swiszcz;
    }

    return 0;
}
