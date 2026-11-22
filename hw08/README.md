ECE 361 - Homework 8

Part 1: Binary Search Tree
I created a binary search tree using C.
The program can add, find, and count nodes.
It can also find the height of the tree.

Part 2: Testing
I tested the tree with different numbers.
The basic tree test passed.
The bonus remove test also passed.
The memory test showed 0 leaks.

Part 3: Tree Height
I tested a tree with 7 numbers.
The result was size 7 and height 3.

When numbers are added in sorted order,
the tree becomes taller.
When numbers are added in a mixed order,
the tree can be shorter.
A taller tree may need more visits to find a number.
Part 3: Tree Height

Increasing order:
n 1023, height 1023

Shuffled order:
n 1023, height 23

When numbers are inserted in increasing order, the tree becomes very tall because each new number goes to the right. This means a search may need to visit many nodes.

When numbers are inserted in random order, the tree is shorter, so a search usually needs fewer visits.
