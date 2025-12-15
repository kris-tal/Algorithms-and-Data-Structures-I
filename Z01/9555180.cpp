#include <iostream>
#include <vector>
#include <algorithm>

struct action {
    int time;
    int type;
    int agent;
};

int bush_photoshoot(std::vector<action> actions, std::vector<int> photos) {
    std::vector<long long> photos_taken(photos.size(), 0);
    long long photo_count = 0;
    for(action a : actions) {
        if(a.type == 0) photos_taken[a.agent] = photo_count;
        else if(a.type == 1) {
            photo_count += std::max((long long)0, photos[a.agent] - (photo_count - photos_taken[a.agent]));
        }
    }
    return photo_count;
}

int main() {
    int q, n;
    std::cin >> q;
    

    while(q--) {
        std::cin >> n;
        std::vector<action> actions(2 * n);
        std::vector<int> photos(n);

        for(int i = 0; i < n; i++) {
            int a, b, c;
            std::cin >> a >> b >> c;
            photos[i] = c;
            actions[i].agent = actions[n + i].agent = i;
            actions[i].type = 0;
            actions[n + i].type = 1;
            actions[i].time = a;
            actions[n + i].time = b;
        }

        std::sort(actions.begin(), actions.end(), [](const action &a, const action &b){
                    if(a.time != b.time) return a.time < b.time;
                    return a.type < b.type; }); /////

        std::cout << bush_photoshoot(actions, photos) << "\n";
    }

    return 0;
}