#ifndef S03_HPP
#define S03_HPP

#include <iostream>
#include <vector>

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


#endif