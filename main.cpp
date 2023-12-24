#include <bits/stdc++.h>
#define fast std::cin.tie(0);std::ios_base::sync_with_stdio(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const ll RBN = 1e9+7;
const ll RSN = -(1e9+7);
const double PI = 3.141592653589793;
//mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); ll gen(){return rnd()%100;}

struct chars {
    ll count;
    vector<char> this_char;
    ll code = 0;
};

struct Node
{
    char x;
    Node* l = nullptr;
    Node* r = nullptr;
    string code = "";
    Node(ll x) : x(x), l(nullptr), r(nullptr){};
    Node() = default;
};

struct BST {
    Node *root = nullptr;

    Node *find(Node *node, char x) {
        if (node == nullptr) return nullptr;
        if (node->x == x) return node;
        if (node->x > x) {
            return find(node->l, x);
        } else {
            return find(node->r, x);
        }
    }

    Node *insert(Node *node, ll x) {
        if (root == nullptr) {
            Node *new_root = new Node;
            new_root->x = x;
            new_root->l = new_root->r = nullptr;
            root = new_root;
            return root;
        }
        if (node == nullptr) {
            return new Node(x);
        } else if (x < node->x) {
            node->l = insert(node->l, x);
        } else if (x > node->x) {
            node->r = insert(node->r, x);
        }
        return node;
    }

    void display(Node* node) {
        if (node == nullptr) {
            return;
        }
        display(node->l);
        cout << node->x << ": ";
        for (ll i = node->code.size()-1; i >= 0; i--) {
            cout << node->code[i];
        }
        cout << '\n';
        display(node->r);
    }
};

struct MinHeap {
    //non-increasing
    vector<chars> heap;

    void sift_up(ll index) {
        while (index > 0 && heap[(index-1)/2].count > heap[index].count) {
            ll parent = (index-1)/2;
            swap(heap[index],heap[parent]);
            index = parent;
        }
    }
    void sift_down(ll index) {
        while (2*index+1 < heap.size()) {
            ll left = 2 * index + 1;
            ll right = 2 * index + 2;
            ll j = left;
            if ((right < heap.size()) && (heap[right].count < heap[left].count)) {
                j = right;
            }
            if (heap[index].count <= heap[j].count) {
                break;
            }
            swap(heap[index], heap[j]);
            index = j;
        }
    }

    void insert(chars value) {
        heap.push_back(value);
        sift_up(heap.size()-1);

    }
    chars extract_min() {
        chars value = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        sift_down(0);
        sift_up(heap.size()-1);
        return value;
    }
};


signed main() {
    vector<char> saved;
    fast;
    MinHeap mh;
    BST bst;
    chars novels[26];
    for (ll i = 0; i < 26; i++) {
        novels[i].count = 0;
        novels[i].this_char.push_back((char) ('a' + i));
    }
    char c;
    ll count = 0;
    while (cin >> c) {
        if (c == '1') {
            break;
        }
        count++;
        novels[c-'a'].count++;
        saved.push_back(c);
    }
    for (ll i = 0; i < 26; i++) {
        if (novels[i].count != 0) {
            mh.insert(novels[i]);
            bst.insert(bst.root,novels[i].this_char[0]);
        }
    }
    ll charscount = 0;
    while (true) {
        chars first = mh.extract_min();
        chars second = mh.extract_min();
        //
        charscount += first.count + second.count;
        chars total;
        total.count = first.count+second.count;
        for (ll i = 0; i < first.this_char.size(); i++) {
            total.this_char.push_back(first.this_char[i]);
            Node* cur = bst.find(bst.root, first.this_char[i]);
            cur->code += "0";
        }
        for (ll i = 0; i < second.this_char.size(); i++) {
            total.this_char.push_back(second.this_char[i]);
            Node* cur = bst.find(bst.root, second.this_char[i]);
            cur->code += "1";
        }
        for (ll i = 0; i < total.this_char.size(); i++) {
            novels[total.this_char[i] - 'a'].code++;

        }
        if (total.count == count) {
            break;
        }
        mh.insert(total);
    }
    ll ans = 0;
    for (ll i = 0; i < 26; i++) {
        ans += novels[i].code * novels[i].count;
    }
    cout << "length: " << ans << '\n';
    cout << "Codes: \n";
    bst.display(bst.root);
    cout << "Message: \n";
    for (ll i = 0; i < saved.size()-1; i++) {
        Node *x = bst.find(bst.root, saved[i]);
        for (ll i = x->code.size() - 1; i >= 0; i--) {
            cout << x->code[i];
        }
    }


    return 0;
}

#this awfull code needs to rewrite
