#pragma once

// Color codes for graph traversal (White = unvisited, Gray = processing, Black = processed)
#define WHITE  0
#define GRAY   1 
#define BLACK  2

#define _CRT_SECURE_NO_WARNINGS // Disables warnings related to unsafe functions in MSVC.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// ---- Graph Representation ----

// Defines an edge in the graph with a neighbor node and associated cost.
typedef struct {
    int neighbor;
    int cost;
} Edge;

// Represents a node in the adjacency list (linked list of edges).
typedef struct edge_node {
    Edge e;
    struct edge_node* next;
} EdgeNode;

// Represents an adjacency list for a given graph node.
typedef struct {
    EdgeNode* head;
    EdgeNode* tail;
} EdgeList;

// ---- Prim's Algorithm Structures ----

// Represents a candidate node in Prim's priority queue.
typedef struct {
    int computer; // Node identifier
    int min;      // Minimum cost to reach this node
} Candidate;

// Doubly linked list node for Prim's priority queue.
typedef struct candidate_node {
    Candidate c;
    struct candidate_node* next;
    struct candidate_node* prev;
} CandidateNode;

// Doubly linked list for managing candidates in Prim's priority queue.
typedef struct {
    CandidateNode* head;
    CandidateNode* tail;
} CandidateList;

int main(); // Forward declaration of the main function.

// ---- Function Declarations ----

// **A: Graph Construction & Management**
EdgeNode* Make_list_With_Dummy(); // Creates an adjacency list with dummy head & tail nodes.
EdgeNode* Create_New_Node(int neighbor, int cost); // Creates a new edge node.
EdgeList* build_net(int n); // Constructs the network graph.
void Sort_List(EdgeList* net, EdgeNode* node); // Inserts an edge into the adjacency list in sorted order.
void printNet(EdgeList* list, int len); // Prints the entire graph.
void print_list_it(EdgeNode* head); // Iterates through an adjacency list and prints its contents.
void freeEdgeList(EdgeList* Net, int n); // Frees allocated memory for the graph.
bool Check_Edge(EdgeList* net, int a, int b); // Check if the connection is already set.

// **B: Prim's Algorithm Functions**
int* build_prim_tree(EdgeList Net[], int n); // Builds the Minimum Spanning Tree using Prim's Algorithm.
int* buildPrim(int n); // Initializes the MST parent array.
bool* buildIntList(int n); // Initializes a boolean array for tracking visited nodes.
int* buildMinArr(int n); // Initializes an array for minimum edge weights.
CandidateList* buildPriority(int vNum, EdgeList* Net, CandidateNode*** location); // Initializes the priority queue.
void print_list_Com(CandidateNode* head); // Prints the priority queue for debugging.
CandidateList* makeEmptyCandidList(); // Creates an empty candidate list for Prim's Algorithm.
int deleteMin(CandidateList* priority, CandidateNode** location); // Removes the minimum-cost node from the priority queue.
void decreaseKey(CandidateNode** location, int v, int minCost); // Updates a node's cost in the priority queue.
void freeFun(int* minArr, bool* inT, CandidateNode** location, CandidateList* priority); // Frees allocated memory for Prim's Algorithm.
void freeCandidateList(CandidateList* list); // Frees all memory allocated for the priority queue.

// **C: Path Construction Functions**
void addToEnd(EdgeList* ComPath, EdgeNode* newNode); // Adds a node to the end of an adjacency list.
EdgeList* build_paths(int* Prim, int n); // Builds paths based on the MST from Prim's Algorithm.

// **D: Pathfinding Functions**
void find_and_print_path(EdgeList* primpath, int size, int first, int last); // Finds and prints the shortest path between two nodes.
int* Findpath(EdgeList* primpath, int* color, int* parent, int first, int last); // Wrapper function for recursive pathfinding.
int* Findpathrec(EdgeList* primpath, int* color, int* parent, int first, int last); // Recursive function to find a path.
int printpathrec(int first, int last, int* parent); // Recursively prints a found path.

// **Debugging Functions**
void debug_print_graph(EdgeList* primpath, int size); // Prints the graph structure for debugging.
void find_and_print_path_with_debug(EdgeList* primpath, int size, int first, int last); // Debugging version of pathfinding.