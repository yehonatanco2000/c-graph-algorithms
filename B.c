#include "pro.h"

int* build_prim_tree(EdgeList Net[], int n) {
    // Implements Prim's Algorithm to build a Minimum Spanning Tree (MST).
    int v0 = 0, i, min, v;

    // Allocate memory for necessary arrays.
    int* prim = buildPrim(n);   // Stores the MST parent relationships.
    int* minArr = buildMinArr(n); // Stores minimum edge weights.
    bool* inT = buildIntList(n); // Tracks nodes already added to the MST.

    // Allocate memory for candidate locations.
    CandidateNode** location = (CandidateNode**)calloc(n, sizeof(CandidateNode*));
    if (location == NULL) {
        printf("memory error");
        exit(1); // Exit if memory allocation fails.
    }

    // Build a priority queue for edge selection.
    CandidateList* priority = buildPriority(n, Net, &location);
    minArr[v0] = 0; // Initialize starting node cost to 0.
    prim[v0] = -1;  // Root node has no parent.

    // Process nodes until priority queue is empty.
    while (priority->head->next != priority->tail) {
        int u = deleteMin(priority, location); // Extract minimum-cost node.

        if (minArr[u] == INT_MAX) {
            printf("Cannot build Prim"); // If node has INT_MAX cost, MST cannot be formed.
            exit(1);
        }
        else {
            inT[u] = true; // Mark node as added to MST.

            // Iterate through the neighbors of the current node.
            EdgeNode* uNeighbor = Net[u].head->next;
            while (uNeighbor != Net[u].tail) {
                v = uNeighbor->e.neighbor;

                // If `v` is not in MST and its cost is lower, update its information.
                if ((!inT[v]) && (uNeighbor->e.cost < minArr[v])) {
                    minArr[v] = uNeighbor->e.cost; // Update minimum cost.
                    prim[v] = u; // Set parent node in MST.
                    decreaseKey(location, v, uNeighbor->e.cost); // Update priority queue.
                }
                uNeighbor = uNeighbor->next;
            }
        }
    }

    // Free allocated memory before returning the MST.
    freeFun(minArr, inT, location, priority);
    return prim;
}

int* buildPrim(int n) {
    // Allocates and initializes the parent array for Prim's Algorithm.
    int* prim = (int*)malloc(sizeof(int) * n);
    if (prim == NULL) {
        printf("memory error");
        exit(1);
    }

    for (int i = 0; i < n; i++)
        prim[i] = -1; // Initialize all nodes with no parent.

    return prim;
}

bool* buildIntList(int n) {
    // Allocates and initializes a boolean array to track visited nodes.
    bool* inT = (bool*)calloc(n, sizeof(bool));
    if (inT == NULL) {
        printf("memory error");
        exit(1);
    }
    return inT;
}

int* buildMinArr(int n) {
    // Allocates and initializes an array for minimum edge weights.
    int* min = (int*)malloc(n * sizeof(int));
    if (min == NULL) {
        printf("memory error");
        exit(1);
    }

    for (int i = 0; i < n; i++)
        min[i] = INT_MAX; // Initialize all nodes with max cost.

    return min;
}

CandidateList* buildPriority(int vNum, EdgeList* Net, CandidateNode*** location) {
    // Creates and initializes a priority queue for Prim's Algorithm.

    CandidateList* candidLst = makeEmptyCandidList();
    CandidateNode* tempHead = candidLst->head;

    for (int i = 0; i < vNum; i++) {
        // Allocate a new candidate node.
        CandidateNode* candNode = (CandidateNode*)malloc(sizeof(CandidateNode));
        if (candNode == NULL) {
            printf("memory error");
            exit(1);
        }

        candNode->c.computer = i; // Assign node index.
        candNode->c.min = INT_MAX; // Default cost to maximum.

        (*location)[i] = candNode; // Store location reference.

        // Insert node into the priority queue.
        tempHead->next = candNode;
        candNode->prev = tempHead;
        tempHead = candNode;
    }

    // Link the last node to the priority queue tail.
    tempHead->next = candidLst->tail;
    candidLst->tail->prev = tempHead;

    return candidLst;
}

void print_list_Com(CandidateNode* head) {
    // Iteratively prints the priority queue of candidates.
    head = head->next;
    while (head->next->next != NULL) {
        printf(" COM: %d, MIN: %d\n", head->c.computer, head->c.min);
        head = head->next;
    }
    printf("\n");
}

CandidateList* makeEmptyCandidList() {
    // Creates an empty candidate list with dummy head and tail nodes.

    CandidateList* candLst = (CandidateList*)calloc(1, sizeof(CandidateList));
    if (candLst == NULL) {
        printf("memory error");
        exit(1);
    }

    candLst->head = (CandidateNode*)calloc(1, sizeof(CandidateNode));
    candLst->tail = (CandidateNode*)calloc(1, sizeof(CandidateNode));
    if (candLst->head == NULL || candLst->tail == NULL) {
        printf("memory error");
        exit(1);
    }

    // Initialize head and tail links.
    candLst->head->prev = NULL;
    candLst->tail->next = NULL;
    candLst->head->next = candLst->tail;
    candLst->tail->prev = candLst->head;

    // Assign default values to dummy nodes.
    candLst->head->c.computer = -1;
    candLst->tail->c.computer = -1;
    candLst->head->c.min = INT_MAX;
    candLst->tail->c.min = INT_MAX;

    return candLst;
}

int deleteMin(CandidateList* priority, CandidateNode** location) {
    // Removes the node with the minimum cost from the priority queue.

    CandidateNode* curr = priority->head->next;
    CandidateNode* minComVal = curr;
    int v;

    if (curr == priority->tail) {
        printf("Priority list is empty!\n");
        return -1;
    }

    while (curr != priority->tail) {
        if (curr->c.min < minComVal->c.min)
            minComVal = curr;
        curr = curr->next;
    }

    v = minComVal->c.computer;

    // Remove node from the list and free memory.
    minComVal->prev->next = minComVal->next;
    minComVal->next->prev = minComVal->prev;
    location[minComVal->c.computer] = NULL;
    free(minComVal);

    return v;
}

void decreaseKey(CandidateNode** location, int v, int minCost) {
    // Updates the minimum cost of node `v` in the priority queue.
    if (location[v] != NULL) {
        CandidateNode* node = location[v];
        node->c.min = minCost;
    }
}

void freeFun(int* minArr, bool* inT, CandidateNode** location, CandidateList* priority) {
    // Frees allocated memory for Prim's Algorithm.
    freeCandidateList(priority);
    free(inT);
    free(minArr);
    free(location);
}

void freeCandidateList(CandidateList* list) {
    // Frees all memory allocated for the priority queue.
    CandidateNode* curr = list->head;
    while (curr != NULL) {
        CandidateNode* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}