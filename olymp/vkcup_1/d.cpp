#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

bool isletter(char c) {
    return c >= 'a' && c <= 'z';
}

typedef struct Node {
    struct Node *parent;
    struct Node *child[30];

    string data;

    bool end;
} Node;

Node *root;

Node *create(Node *parent) {
    Node *n = new Node;
    n->parent = parent;
    n->end = false;
    return n;
}

Node *split_node(Node *n, int p) {
    //cout << "split node: " << n->data << endl;
    string new_data = n->data.substr(p, n->data.size());
    n->data = n->data.substr(0, p);
    //cout << new_data << endl << n->data << endl;

    Node *ch = create(n);
    ch->data = new_data;
    ch->end = n->end;
    n->end = false;
    for (int i = 0; i < 30; ++i) {
        ch->child[i] = n->child[i];
        n->child[i] = NULL;
    }
    n->child[new_data[0] - 'a'] = ch;

    return ch;
}

int cost_word(Node *n, string s) {
    //cout << "cost_word: n->data: '" << n->data << "', s: '" << s << "'\n";
    for (int i = 0; i < n->data.size(); ++i) {
        if (i >= s.size()) {
   //         cout << "resp -1"<< endl;
            return -1;
        }
        if (n->data[i] != s[i]) {
   //         cout << "resp -1"<< endl;
            return -1;
        }
    }
    if (s.size() > n->data.size()) {
        if (n->child[s[n->data.size()] - 'a'] != NULL) {
            int r = cost_word(n->child[s[n->data.size()] - 'a' ], s.substr(n->data.size(), s.size()));
   // cout << "###\n";
   //         cout << "r: " << r << endl;
            if (r == -1) {
   //         cout << "resp " << r << endl;
                return r;
            }
   //         cout << "resp " << r + n->data.size() << endl;
            return r + n->data.size();
        } else {
   //         cout << "resp -1"<< endl;
            return -1;
        }
    }
    if (n->end) {
   //         cout << "resp 1"<< endl;
        return 1;
    } else {
            //cout << "resp -1"<< endl;
        return -1;
    }
}

void add_word(Node *n, string s) {

    //cout << "add_word: n->data: '" << n->data << "', s: '" << s << "'\n";

    if (n->data.size() == 0) {
        int t = 0;
        for (int i = 0; i < 30; ++i) if (n->child[i] != NULL) t++;
        if (t == 0){
            n->data = s;
            n->end = true;
            return;
        }
    }
    for (int i = 0; i < n->data.size(); ++i) {
        if (i >= s.size()) {
            split_node(n, i);
            return;
        }
        if (n->data[i] != s[i]) {
            Node *ch = split_node(n, i);
            break;
        }
    }
    if (s.size() > n->data.size()) {
        if (n->child[s[n->data.size()] - 'a'] == NULL) {
            n->child[s[n->data.size()] - 'a'] = create(n);
        }
        add_word(n->child[s[n->data.size()] - 'a'], s.substr(n->data.size(), s.size()));
        return;
    }
    n->end = true;
}

int test() {                 
    string s = "asdqwe";
    add_word(root, s);
    s = "asdasd";
    add_word(root, s);

    s = "asdasd";
    cout << cost_word(root, s) << endl;
    s = "asd";
    cout << cost_word(root, s) << endl;
    cout <<"****\n";
    s = "asdqwe";
    cout << cost_word(root, s) << endl;

}

long long ans = 0;

int main() {
    char c;
    string s;

    root = create(NULL);

    while (true) {
        c = getchar();
        if (c <= 0) break;
        if (!isletter(c)){
            ans++;
            if (s.size() < 1) continue;

            int c = cost_word(root, s);
            if (c > 0) {
                ans += c+1;
                s = "";
                continue;
            }
            add_word(root, s);
            ans += s.size();
            s = "";
            continue;
        }
        s += c;
    }
    cout << ans << endl;
}
