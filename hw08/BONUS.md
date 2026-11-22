HW8 Bonus: bst_remove

Original tree:

        27
       /  \
     14    35
    / \   /  \
   10 19 31  42

1. Remove 10 (leaf node):

        27
       /  \
     14    35
       \   / \
       19 31 42

2. Remove 14 (one child):

        27
       /  \
      19   35
          /  \
         31  42

3. Remove 27 (two children):

        31
       /  \
      19   35
             \
             42

The remove function deletes one key from the tree.
It handles nodes with zero, one, or two children.
For two children, it uses the smallest key
from the right subtree.
