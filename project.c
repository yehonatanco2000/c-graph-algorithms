#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "pro.h"

int main()
{
    int n, i;
    EdgeList* Net;
    int* Prim;
    EdgeList* PrimPath;
    int first, last;
    scanf("%d", &n);
    Net = build_net(n);
    Prim = build_prim_tree(Net, n);
    PrimPath = build_paths(Prim, n);
    scanf("%d%d", &first, &last);
    find_and_print_path(PrimPath, n, first, last);
    freeEdgeList(Net, n);
    free(Prim);
    freeEdgeList(PrimPath, n);

    return 0;
}