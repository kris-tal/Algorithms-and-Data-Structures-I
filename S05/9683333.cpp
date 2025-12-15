#include <iostream>
#include <random>
#include <climits>
#include <utility>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, INT_MAX);

struct Node {
    Node *left{};
    Node *right{};
    int val{};
    size_t h = dist(gen);
    int size = 1;   //rozmiar poddrzewa ktorego korzeniem jest ten node
    bool rev = false;

    Node(int v) : val(v) {}
};

int getSize(Node* node) {       //
    if(!node) return 0;
    return node->size;
}

void reverse(Node* parent, Node* node) {      //
    if(!node) return;
    node->rev ^= parent->rev;
}

void push(Node* node) {     //
    if(!node->rev) return;
    std::swap(node->left, node->right);
    reverse(node, node->right);
    reverse(node, node->left);
    node->rev = false;
}

void update(Node* node) {
    node->size = getSize(node->left) + getSize(node->right) + 1;
}

Node* merge(Node *p, Node* q) {     //
    if(!p) return q;
    if(!q) return p;
    if(p->h > q->h) {
        push(p);
        p->right = merge(p->right, q);
        update(p);
        return p;
    }
    else {
        push(q);
        q->left = merge(p, q->left);
        update(q);
        return q;
    }
}

std::pair<Node*, Node*> split(Node *R, int pos) {   ////!!
    if(!R) return {nullptr, nullptr};
    push(R);
    if(getSize(R->left) < pos) {
        auto [a, b] = split(R->right, pos - getSize(R->left) - 1);  //
        R->right = a;
        update(R);
        return {R, b};
    }
    else {
        auto [a, b] = split(R->left, pos);
        R->left = b;
        update(R);
        return {a, R};
    }
}

Node* getLeft(Node* R) {
    if(!R->rev) {
        if(R->left == nullptr) return R;
        else return getLeft(R->left);
    }
    else {
        if(R->right == nullptr) return R;
        else return getLeft(R->right);
    }
}

Node* getRight(Node* R) {
    if(!R->rev) {
        if(R->right == nullptr) return R;
        else return getRight(R->right);
    }
    else {
        if(R->left == nullptr) return R;
        else return getRight(R->left);
    }
}

void clean(Node* root) {
    if (!root) return;
    clean(root->left);
    clean(root->right);
    delete root;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int z;
    std::cin >> z;

    while(z--) {
        int n, q;
        std::cin >> n >> q;
        Node *root = nullptr;

        for(int i = 1; i <= n; i++) {
            Node* next = new Node(i);
            root = merge(root, next);
        }

        for(int i = 0; i < q; i++) {
            int x, y;
            std::cin >> x >> y;
            x--;
            auto [a, b] = split(root, x);
            auto [c, d] = split(b, y - x);

            std::cout << getLeft(c)->val << " " << getRight(c)->val << "\n";
            
            if(c) c->rev = !c->rev;
            Node *R = merge(a, c);
            root = merge(R, d);
        }

        clean(root);
    }


    return 0;
}