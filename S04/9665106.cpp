#include <iostream>
#include <vector>

//===================================== SZABLON ==================================

int my_lg(int n) {
    if (n == 0) return 0;
    int power = 1;
    int p = 0;
    while (power * 2 <= n) {
        power *= 2;
        p++;
    }
    return p;
}

template<typename Value, typename Modifier>
struct Node {
    Value val;
    Modifier mod;
    operator Value() const {
        return mod(val);
    }
};

template<typename Value, typename Modifier>
class SegmentTree {
    std::vector<Node<Value, Modifier>> T;
    int N;
    void push(std::size_t v);
    void update(std::size_t v);
    void update(std::size_t begin, std::size_t end, Modifier modifier, std::size_t v, std::size_t p, std::size_t q);
    Value query(std::size_t begin, std::size_t end, std::size_t v, std::size_t p, std::size_t q) const;

public:
    SegmentTree(std::size_t n, Value value = {});
    SegmentTree(const std::vector<Value>& values);
    Value query(std::size_t begin, std::size_t end) const;
    void update(std::size_t begin, std::size_t end, Modifier modifier);
    
};

template<typename Value, typename Modifier>
SegmentTree<Value, Modifier>::SegmentTree(std::size_t n, Value value) {
    //N = 1 << my_lg(n);
    N = 1 << std::__lg(n);
    if(N != n) N = N << 1;
    T.resize(2 * N);

    for(int i = 0; i < n; i++) {
        T[i + N].val = value;
    }

    for(int i = N - 1; i > 0; i--) T[i].val = (Value)T[i * 2] + (Value)T[i * 2 + 1];
}

template<typename Value, typename Modifier>
SegmentTree<Value, Modifier>::SegmentTree(const std::vector<Value>& values) {
    //N = 1 << my_lg(values.size());
    N = 1 << std::__lg(values.size());
    if(N != values.size()) N = N << 1;
    T.resize(2 * N);

    for(int i = 0; i < values.size(); i++) {
        T[i + N].val = values[i];
    }

    for(int i = N - 1; i > 0; i--) T[i].val = (Value)T[i * 2] + (Value)T[i * 2 + 1];
}

template<typename Value, typename Modifier> //
void SegmentTree<Value, Modifier>::push(std::size_t v) {
    T[2 * v].mod = T[v].mod * T[2 * v].mod;
    T[2 * v + 1].mod = T[v].mod * T[2 * v + 1].mod;
    T[v].mod = {};
}

template<typename Value, typename Modifier> //
Value SegmentTree<Value, Modifier>::query(std::size_t begin, std::size_t end) const {
    if(begin >= end || end == 0) return {};
    return query(begin, end, 1, 0, N);
}

template<typename Value, typename Modifier> //
Value SegmentTree<Value, Modifier>::query(std::size_t begin, std::size_t end, std::size_t v, std::size_t p, std::size_t q) const {
    if(p >= q) return {};
    if(q <= begin || p >= end) return {};
    if(p >= begin && q <= end) return T[v];     //zobacz czy nie psuje
    auto s = p + (q - p) / 2;
    return T[v].mod(query(begin, end, 2 * v, p, s) + query(begin, end, 2 * v + 1, s, q));
}

template<typename Value, typename Modifier> //
void SegmentTree<Value, Modifier>::update(std::size_t v) {
    T[v].val = (Value)T[2 * v] + (Value)T[2 * v + 1];     //zbiera mi val + mod
}

template<typename Value, typename Modifier> //
void SegmentTree<Value, Modifier>::update(std::size_t begin, std::size_t end, Modifier modifier) {
    if(begin >= end || end == 0) return;
    update(begin, end, modifier, 1, 0, N);
}

template<typename Value, typename Modifier> // 
void SegmentTree<Value, Modifier>::update(std::size_t begin, std::size_t end, Modifier modifier, std::size_t v, std::size_t p, std::size_t q) {
    if(p > q) return;
    if(q <= begin || p >= end) return;      //nie maja czesci wspolnej
    if(p >= begin && q <= end) {        //zaweira sie i wtedy nakladamy mod na caly przedzial
        T[v].mod = modifier * T[v].mod;
        return;
    }
    auto s = p + (q - p) / 2;       //dzielimy sie na dwa przedzialy
    push(v);        //pushujemy nasz modifier do dzieci
    update(begin, end, modifier, 2 * v, p, s);      //wywolujemy sie na dzieciach
    update(begin, end, modifier, 2 * v + 1, s, q);
    update(v);      //updateujemy val z uwzglednieniem nowych modow na dzieciach
}

//===================================== SZABLON ==================================

struct Value { //
    int counter[2] = {};    //0 ile jest bialych 1 ile jest czarnych
    long long sum[2] = {};     //suma bialych / czarnych
    long long finalsum[2] = {};       //suma z tym pomnozeniem
};

Value operator+(const Value &a, const Value &b) { //
    Value res = {};
    for(int i = 0; i < 2; i++) {
        res.counter[i] = a.counter[i] + b.counter[i];
        res.sum[i] = a.sum[i] + b.sum[i];
        res.finalsum[i] = a.finalsum[i] + b.finalsum[i] + a.counter[i] * b.sum[i];
    }

    return res;
}

struct Modifier {
    long long X[2] = {};
    bool on = false;

    Value operator()(const Value &val) const { //
        Value res;
        for(int i = 0; i < 2; i++) {
            res.counter[i ^ on] = val.counter[i];
            res.sum[i ^ on] = val.sum[i] + X[i] * val.counter[i];
            res.finalsum[i ^ on] = (long long)val.finalsum[i] + X[i] * (long long)val.counter[i] * (1 + val.counter[i]) / 2;      //check
        }

        return res;
    }
};

Modifier operator*(const Modifier &a, const Modifier &b) { //
        Modifier res = {};
        res.on = a.on ^ b.on;
        for(int i = 0; i < 2; i++) {
            res.X[i] = a.X[i ^ b.on] + b.X[i];  //
        }
        
        return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int z;

    std::cin >> z;

    while(z--) {
        int n;
        std::cin >> n;
        std::vector<Value> vec(n, Value{});
        int val;
        for(int i = 0; i < n; i++) {
            std::cin >> val;
                vec[i].counter[0] = 1;
                vec[i].sum[0] = val;
                vec[i].finalsum[0] = val;
        }

        SegmentTree<Value, Modifier> stree(vec);

        int q;
        std::cin >> q;

        for(int i = 0; i < q; i++) {
            int com;
            std::cin >> com;

            int l, r;
            if(com == 1) {
                std::cin >> l >> r;
                Modifier mod = {};
                mod.on = true;
                stree.update(l, r, mod);
            }
            else if(com == 2) {
                int x;
                std::cin >> l >> r >> x;
                Modifier mod = {};
                mod.X[0] = x;       ////
                stree.update(l, r, mod);
            }
            else {
                std::cin >> l >> r;
                std::cout << stree.query(l, r).finalsum[0] << "\n";
            }
        }
    }

    return 0;
}