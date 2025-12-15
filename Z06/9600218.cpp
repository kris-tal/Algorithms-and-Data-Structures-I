/*
Składniki:
2 szklanki mąki pszennej
150 g masła (schłodzonego)
1/2 szklanki cukru
1 łyżeczka proszku do pieczenia
2 żółtka
1 jajko
1–2 łyżki śmietany 18% (opcjonalnie, jeśli ciasto będzie zbyt suche)

Nadzienie:
5–6 jabłek (najlepiej kwaśnych, np. szara reneta)
2 łyżki cukru (lub więcej, do smaku)
1 łyżeczka cynamonu
1 łyżka masła (do podsmażenia jabłek)
Przygotowanie:

Przygotowanie ciasta:
W misce wymieszaj mąkę, cukier i proszek do pieczenia.
Dodaj masło pokrojone w kostkę i rozetrzyj palcami, aż powstanie kruszonka.
Dodaj żółtka, jajko i szybko zagnieć ciasto. Jeśli jest zbyt suche, dodaj łyżkę śmietany.
Podziel ciasto na dwie części (2/3 i 1/3), zawiń w folię i wstaw do lodówki na 30 minut.
Przygotowanie jabłek:
Obierz jabłka, usuń gniazda nasienne i pokrój w plasterki lub kostkę.
Na patelni rozpuść masło, dodaj jabłka, cukier i cynamon. Podsmaż, aż jabłka zmiękną, ale nie rozpadną się. Odstaw do przestygnięcia.
Składanie szarlotki:
Rozgrzej piekarnik do 180°C.
Większą część ciasta rozwałkuj i wyłóż nim dno oraz boki formy do pieczenia (około 24 cm średnicy).
Na ciasto wyłóż przestudzone jabłka.
Resztę ciasta zetrzyj na tarce o grubych oczkach i posyp wierzch jabłek.
Pieczenie:
Piecz przez 40–45 minut, aż wierzch będzie złocisty.
Po wystudzeniu można posypać cukrem pudrem.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    int q;
    std::cin >> q;
    std::vector<std::pair<int, int>> segments;

    auto cmp = [&](int a, int b) {
        return segments[a].first < segments[b].first;
    };

    while(q--) {
        int n;
        std::cin >> n;
        segments.clear();
        segments.resize(n);
        std::vector<std::pair<int, int>> sums(n);
        
        std::priority_queue<int, std::vector<int>, decltype(cmp)> heap(cmp);
        for(int i = 0; i < n; i++) {
            int m, w;
            std::cin >> m >> w;
            segments[i] = {m, w};
            sums[i].first = i;
            sums[i].second = m + w;
        }

        std::sort(sums.begin(), sums.end(), [](std::pair<int, int> a, std::pair<int, int> b){
            return a.second < b.second;
        });

        int heap_weight = 0;

        for(int i = 0; i < n; i++) {
            
            int idx = sums[i].first;
            if(heap.empty() || heap_weight <= segments[idx].second) {
                heap_weight += segments[idx].first;
                heap.push(idx);
            }
            else if(segments[heap.top()].first >= segments[idx].first) {
                heap_weight -= segments[heap.top()].first;
                heap_weight += segments[idx].first;
                heap.pop();
                heap.push(idx);
            }
        }

        std::cout << heap.size() << "\n";
    }

    return 0;
}