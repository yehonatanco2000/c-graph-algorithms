#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "pro.h"

EdgeNode* Make_list_With_Dummy() {
    // Creates a linked list with dummy head and tail nodes.
    EdgeNode* dummy_head, * dummy_tail;
    dummy_head = (EdgeNode*)malloc(sizeof(EdgeNode));
    dummy_tail = (EdgeNode*)malloc(sizeof(EdgeNode));
    if (dummy_head == NULL || dummy_tail == NULL)
        exit(1); // Exit if memory allocation fails.

    // Initialize dummy nodes.
    dummy_head->e.neighbor = dummy_tail->e.neighbor = -1;
    dummy_head->e.cost = dummy_tail->e.cost = 0;
    dummy_head->next = dummy_tail;
    dummy_tail->next = NULL;

    return dummy_head; // Return the head of the linked list.
}

EdgeNode* Create_New_Node(int neighbor, int cost) {
    // Creates a new node representing an edge.
    EdgeNode* new_node;
    new_node = (EdgeNode*)malloc(sizeof(EdgeNode));
    if (new_node == NULL)
        exit(1); // Exit if memory allocation fails.

    // Initialize edge properties.
    new_node->e.neighbor = neighbor;
    new_node->e.cost = cost;
    new_node->next = NULL;

    return new_node;
}

EdgeList* build_net(int n) {
    // Builds an adjacency list representation of a graph with n nodes.
    if (n < 0) {
        printf("Invalid input.");
        exit(1);
    }
    EdgeList* net;
    EdgeNode* Node_a_to_b, * Node_b_to_a;
    int i, M, a, b, price;
    bool IsEdge;

    net = (EdgeList*)malloc(sizeof(EdgeList) * n);
    if (net == NULL) {
        exit(1);
    }
    for (i = 0; i < n; i++) {
        net[i].head = Make_list_With_Dummy(); // Initialize each list with dummy nodes.
        net[i].tail = net[i].head->next;      // The tail points to the dummy tail node.
    }

    printf("Enter the numbers of lines:");
    scanf("%d", &M); // Read the number of edges.

    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &price); // Read edge information.
        if (a > n || a < 0 || b > n || b < 0 || price < 0 || a==b) {
            printf("invalid input");
            freeEdgeList(net, n);
            exit(1);
        }
        IsEdge = Check_Edge(net, a, b); // Check if the connection is already set.
        if (IsEdge) {
            Node_a_to_b = Create_New_Node(b, price);
            Node_b_to_a = Create_New_Node(a, price);

            Sort_List(&net[a], Node_a_to_b); // Insert edge from a to b.
            Sort_List(&net[b], Node_b_to_a); // Insert edge from b to a.
        }
    }

    return net;
}

void Sort_List(EdgeList* net, EdgeNode* node) {
    // Inserts a node into the linked list in a sorted manner.
    EdgeNode* temp;
    temp = net->head; // Start from the head.

    while (temp->next != NULL) {
        if (temp->next == net->tail) { // If next is the dummy tail node, insert before it.
            node->next = temp->next;
            temp->next = node;
            return;
        }
        else {
            // Keep traversing if the neighbor value is larger.
            if (node->e.neighbor > temp->next->e.neighbor && temp->next->e.neighbor != -1)
                temp = temp->next;
            else {
                // Insert the node at the correct position.
                node->next = temp->next;
                temp->next = node;
                return;
            }
        }
    }
}

void printNet(EdgeList* list, int len) {
    // Prints the entire network.
    int i;
    for (i = 0; i < len; i++) {
        printf("source: %d", i);
        print_list_it(list[i].head);
    }
}

void print_list_it(EdgeNode* head) {
    // Iteratively prints the edges of a node.
    head = head->next; // Skip the dummy head node.
    while (head->next != NULL) {
        printf(" dest: %d, price: %d", head->e.neighbor, head->e.cost);
        head = head->next;
    }
    printf("\n");
}

void freeEdgeList(EdgeList* Net, int n) {
    // Frees the dynamically allocated memory of the adjacency list.
    for (int i = 0; i < n; i++) {
        EdgeNode* curr = Net[i].head;
        while (curr != NULL) {
            EdgeNode* next = curr->next;
            if (next != NULL)
                free(curr);
            curr = next;
        }
    }
    free(Net); // Free the entire network.
}


bool Check_Edge(EdgeList* net, int a, int b) {

    EdgeNode* current = net[a].head->next;
    while (current->next != NULL) {
        if (current->e.neighbor == b) {
            printf("Invalid input.\n");
            return 0;
        }
        current = current->next;
    }
    return 1;
}
