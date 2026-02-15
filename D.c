#include "pro.h"

void find_and_print_path(EdgeList* primpath, int size, int first, int last) {
    // Allocates memory and initializes arrays for tracking paths.
    if (first > size || first<0 || last>size || last < 0) {
        printf("invalid input");
        exit(1);
    }
    int* color, * parent;
    color = (int*)malloc(sizeof(int) * size);
    parent = (int*)malloc(sizeof(int) * size);

    if (color == NULL || parent == NULL)
        exit(1); // Exit if memory allocation fails.

    // Initialize arrays: `color` tracks visit state, `parent` tracks path connections.
    for (int i = 0; i < size; i++) {
        color[i] = WHITE; // All nodes initially unvisited.
        parent[i] = -1; // No parent assigned yet.
    }

    // Find the path and print it.
    Findpath(primpath, color, parent, first, last);
    printpathrec(first, last, parent);

    // Free allocated memory after use.
    free(color);
    free(parent);
}

int* Findpath(EdgeList* primpath, int* color, int* parent, int first, int last) {
    // Calls the recursive function to find the path.
    int* path = Findpathrec(primpath, color, parent, first, last);

    if (path == NULL) {
        printf("NO PATH\n"); // Indicates no valid path was found.
    }

    return path;
}

int* Findpathrec(EdgeList* primpath, int* color, int* parent, int first, int last) {
    // Recursive function to search for a path in the graph.

    EdgeNode* current = primpath[first].head->next;
    int neighbor;
    int* path;

    color[first] = GRAY; // Mark the node as being processed.

    // Traverse through adjacency list of `first` node.
    while (current->next != NULL) {
        neighbor = current->e.neighbor;

        if (neighbor == last) { // If we reached the destination, update parent.
            parent[neighbor] = first;
            color[neighbor] = BLACK; // Mark as fully processed.
            return parent;
        }

        // Explore unvisited neighbors recursively.
        if (color[neighbor] == WHITE) {
            parent[neighbor] = first;
            path = Findpathrec(primpath, color, parent, neighbor, last);

            if (path != NULL) // If a valid path is found, return it.
                return path;
        }

        current = current->next;
    }

    color[first] = BLACK; // Mark node as fully processed.
    return NULL; // No path found.
}

int printpathrec(int first, int last, int* parent) {
    // Recursively prints the path from `first` to `last`.

    if (last == first) {
        printf("%d ", last); // Base case: print the first node.
    }
    else {
        printpathrec(first, parent[last], parent); // Recursively print parent nodes.
        printf("%d ", last); // Print the current node after recursion unwinds.
    }

    return 0;
}
