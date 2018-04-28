#include "stdio.h"
#include "stdlib.h"

typedef struct elem{
    struct elem *p, *n;
    int d;
} elem;

elem *root = NULL;

elem *new(int d) {
    elem *ptr = (elem *)malloc(sizeof(elem));
    ptr->d = d;
    ptr->n = NULL;
    ptr->p = NULL;
    return ptr;
}

elem *append(elem *root, elem *e) {
    if (!root) {
        e->n = NULL;
        e->p = e;
        return e;
    }
    elem *tail = root->p;
    tail->n = e;
    e->p = tail;
    root->p = e;
    return root;
}

void delete(elem *e) {
    elem *p = e->p;
    elem *n = e->n;
    if (n && p) {
        p->n = n;
        n->p = p;
    } else {
        if (p) {
            p->n = NULL;
        }
    }

    if (e == root) root = NULL; 

    free(e);
}

int main(){
    int n, k;
    scanf("%d", &n);
    k = n;

    for (int i = 0; i < n; i++){
        int t;
        scanf("%d", &t);
        elem *ptr = new(t);
        root = append(root, ptr);
    }

    elem *pos = root;

    pos = root;
    for (int i = 0; i < n-1; ++i) {
        while (pos && pos->n) {
            if (pos->d == pos->n->d) break;
            pos = pos->n;
        }
        if (pos && pos->n && pos->d == pos->n->d) {
            pos->d += 1;
            delete(pos->n);
            if (pos != root && pos->d == pos->p->d){
                pos = pos->p;
            }
            --k;
        } else {
            break;
        }
    }
    printf("%d\n", k);
    pos = root;
    while (pos) {
        printf("%d ", pos->d);
        pos = pos->n;
    }
    printf("\n");
    return 0;
}
