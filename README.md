# Network Routing & Graph Algorithms Utility

## Overview
A C-based application designed to process complex networks, construct Minimum Spanning Trees (MST), and dynamically compute paths between nodes. This project demonstrates strong foundations in manual memory management, pointer arithmetic, and algorithmic logic.

## Key Features
* **Prim's Algorithm:** Efficiently builds a Minimum Spanning Tree from a given network of computers to find the most cost-effective connectivity.
* **Custom Data Structures:** Implemented dynamic priority queues (CandidateList) and adjacency lists from scratch using doubly linked lists.
* **Pathfinding & Search:** Utilizes Depth-First Search (DFS) with state-coloring logic (White/Gray/Black) to extract and print exact routes between specified nodes.
* **Strict Memory Management:** Ensured zero memory leaks through meticulous dynamic allocation and deallocation (`malloc`, `calloc`, `free`) across all graph structures.

## Technologies
* **Language:** C
* **Concepts:** Graph Theory, Data Structures, Pointers, Dynamic Memory Allocation, Recursion.

## Project Structure
* `A.c` - Adjacency list construction and management.
* `B.c` - Prim's Algorithm implementation and Priority Queue logic.
* `C.c` - MST path building.
* `D.c` - Pathfinding search (DFS) and recursive printing.
* `project.c` - Main entry point and execution flow.
* `pro.h` - Header file containing structures and function prototypes.

## How to Compile & Run (Visual Studio)
1. Create a new "Empty Project" in Visual Studio.
2. Add all `.c` and `.h` files to the project.
3. Build the solution (`Ctrl + Shift + B`).
4. Run the program (`Ctrl + F5`).
5. The program will prompt for input: 
   - Number of nodes.
   - Number of edges.
   - For each edge: `source`, `destination`, and `cost`.
   - Start and End nodes for pathfinding.
