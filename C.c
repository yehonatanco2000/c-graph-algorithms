#include "pro.h"

EdgeList* build_paths(int* Prim, int n) {
    // Creates an adjacency list representation of Prim's minimum spanning tree (MST).
    int i, j;
    EdgeNode* newNode1, * newNode2;

    // Allocate memory for the adjacency list.
    EdgeList* PrimPath = (EdgeList*)malloc(sizeof(EdgeList) * n);

    // Initialize each list with dummy head and tail nodes.
    for (i = 0; i < n; i++) {
        PrimPath[i].head = Make_list_With_Dummy();
        PrimPath[i].tail = PrimPath[i].head->next;
    }

    // Construct the MST paths based on the `Prim` array.
    for (i = 0; i < n; i++) {
        // Create bidirectional edges between nodes.
        if (Prim[i] != -1) {
            newNode1 = Create_New_Node(Prim[i], 0); // Edge from node `i` to its parent.
            newNode2 = Create_New_Node(i, 0);      // Edge from parent to node `i`.

            // Insert edges into the sorted adjacency list.
            Sort_List(&PrimPath[i], newNode1);
            Sort_List(&PrimPath[Prim[i]], newNode2);
        }
    }

    return PrimPath; // Return the adjacency list representation of the MST.
}