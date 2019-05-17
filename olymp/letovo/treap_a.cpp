#include <bits/stdc++.h>

using namespace std;

typedef int64_t ii;

typedef struct item_s {
    ii key;
    ii prior;
    int n;
    int parent;
    item_s *l, *r;
} item_t;

typedef item_t* item;

item create(ii key, ii prior, int n) {
    item p = (item)malloc(sizeof(item_t));
    p->key = key;
    p->prior = prior;
    p->n = n;
    p->parent = 0;
    p->l = p->r = NULL;

    return p;
}

void split(item t, ii key, item &l, item &r) {
    if (!t) {
        l = l = NULL;
    } else if (key < t->key) {
        split(t->l, key, l, t->l);
        r = t;
    } else {
        split(t->r, key, t->r, r);
        l = t;
    }
}

void merge(item &t, item l, item r) {
	if (!l || !r) {
		t = l ? l : r;
    //} else if (l->prior > r->prior) {
    } else if (l->prior < r->prior) {
		merge(l->r, l->r, r);
        t = l;
    } else {
		merge(r->l, l, r->l);
        t = r;
    }
}

void insert(item &t, item i) {
  //item l=NULL, r=NULL;
  //split(t, i->key, l, r);
  //merge(i, l, i);
  //merge(i, i, r);
  //
  //t = i;
  //
  //return;

	if (!t) {
		t = i;
    } else if (i->prior > t->prior) {
    	split(t, i->key, i->l, i->r);
        t = i;
    } else {
    	insert(i->key < t->key ? t->l : t->r, i);
    }
  //} else if (i->prior > t->prior) {
  //	split(t, i->key, i->l, i->r);
  //    t = i;
  //} else {
  //	insert(i->key < t->key ? t->l : t->r, i);
  //}
}

int number(item t) {
    if (t) return t->n;
    return 0;
}

void walk(item t, item parent) {
    if (!t) return;

    //cout << t->key << ' ' << t->prior << ": ";
    
    t->parent = number(parent);

  //cout << number(parent) << ' ';
  //cout << number(t->l) << ' ';
  //cout << number(t->r) << endl;

    walk(t->l, t);
    walk(t->r, t);
}


int main() {
    int n;
    ii a, b;
    item root = NULL;
    cin >> n;
    item *list = (item*)malloc(n*sizeof(item));

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        item p = create(a, -b, i+1);
        list[i] = p;
        insert(root, p);
    }

    cout << "YES\n";

    walk(root, NULL);

    for (int i = 0; i < n; ++i) {
        cout << list[i]->parent << ' ';
        cout << number(list[i]->l) << ' ';
        cout << number(list[i]->r) << endl;
        
    }
    return 0;
}
