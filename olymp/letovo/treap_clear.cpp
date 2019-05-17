#include <bits/stdc++.h>

using namespace std;

typedef int64_t ii;

typedef struct item_s {
    ii key;
    ii prior;
    item_s *l, *r;
} item_t;

typedef item_t* item;

item create(ii key, ii prior) {
    item p = (item)malloc(sizeof(item_t));
    p->key = key;
    p->prior = prior;
    p->l = p->r = NULL;

    return p;
}

void split(item t, ii key, item &l, item &r) {
    if (!t) {
        l = l = NULL;
    } else if (key < t->key) {
        r = t;
        split(t->l, key, l, t->l);
    } else {
        l = t;
        split(t->r, key, t->r, r);
    }
}

void merge(item &t, item l, item r) {
	if (!l || !r) {
		t = l ? l : r;
    } else if (l->prior > r->prior) {
        t = l;
		merge (l->r, l->r, r);
    } else {
        t = r;
		merge (r->l, l, r->l);
    }
}

void insert(item &t, item i) {
	if (!t) {
		t = i;
    } else if (i->prior > t->prior) {
		split (t, i->key, i->l, i->r);
        t = i;
    } else {
		insert (i->key < t->key ? t->l : t->r, i);
    }
}


int main() {
    int n;
    ii a, b;
    item root = NULL;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        item p = create(a, b);
        insert(root, p);
    }

    return 0;
}
