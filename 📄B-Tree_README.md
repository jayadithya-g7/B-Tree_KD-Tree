# B-Tree_&_KD-Tree
------------------

B-TREE :-
------

B-trees are balanced tree data structures commonly used in computer science for efficient storage and retrieval of data in a sorted order. 

Here are some basics :-

Definition :-
----------

A B-tree is a self-balancing tree data structure that maintains sorted data and allows for efficient searching, insertion, and deletion operations.

Balanced Tree :-
-------------

B-trees are balanced, meaning that, regardless of the number of elements stored in the tree, the depth of the tree remains relatively constant. This ensures that operations like searching, insertion, and deletion have logarithmic time complexity.

Node Structure :-
--------------

Each node of a B-tree can contain multiple keys and pointers to child nodes. The number of keys in a node determines the order of the B-tree.

Order of a B-tree :-
------------------

The order of a B-tree refers to the maximum number of children a node can have. A B-tree of order m can have at most m children and m - 1 keys.

Properties :-
-----------

All leaves are at the same level.

A node can have at most m children.

A node, except for the root, can have at least ⌈m/2⌉ children.

The root has at least two children if it is not a leaf node.

Search Operation :-
-----------------

Searching in a B-tree starts from the root node and moves downwards until the desired key is found or the leaf level is reached. This is similar to binary search but with multiple children per node.

Insertion Operation :-
--------------------

To insert a new key, the tree is traversed to find the appropriate leaf node. If the leaf node is not full, the key is inserted into it. If the leaf node is full, it's split, and the median key is promoted to the parent node.

Deletion Operation :-
-------------------

Deleting a key from a B-tree involves finding the key to be deleted and removing it from the leaf node. If the node becomes underflowed (i.e., having fewer keys than required), it can borrow keys from its siblings or merge with them to maintain the B-tree properties.

Applications :-
--------------

B-trees are widely used in databases and file systems where large amounts of data need to be stored and efficiently accessed. They provide good performance for both read and write operations.

Overall, B-trees are versatile data structures that strike a balance between memory usage and performance, making them suitable for a wide range of applications requiring efficient data storage and retrieval.

-----------------------------------------------------------------------------------------------------------------------------

Implementation :-
--------------

Insertion :-
---------

Start from Root: Begin the insertion process by starting at the root of the B-tree.
   
Search for Leaf Node: Traverse the B-tree from the root to find the appropriate leaf node where the new key should be inserted. Follow child pointers based on the comparison of the key with the keys in each node until you reach a leaf node.

Insert Key in Leaf Node: Insert the new key into the leaf node. If the leaf node has space for the new key (less than the maximum allowed number of keys), insert the key at its sorted position in the node. Otherwise, perform a split operation.

Splitting Full Leaf Node (if necessary): If the leaf node is full after inserting the new key, split it into two nodes. Distribute the keys evenly between the two nodes, ensuring that the median key moves up to the parent node. Adjust pointers accordingly.

Update Parent Nodes: After inserting the new key and potentially splitting nodes, update the parent nodes' keys and pointers to reflect any changes. If necessary, recursively update parent nodes and perform splits until the root node is reached.

Root Split (if necessary): If the root node splits during insertion, create a new root node and make the old root node its child. Update pointers accordingly.

![image](https://github.com/CybersecurityDSA/B-Tree_KD-Tree/assets/144100792/5c70ed58-248d-40dc-92e1-b812f6c04c88)


-----------------------------------------------------------------------------------------------------------------

Searching :-
----------
Start from Root: Begin the search process by starting at the root of the B-tree.
   
Traverse the Tree: Follow child pointers based on the comparison of the search key with the keys in each node. Move down the tree until you either find the key in a leaf node or determine that the key is not present in the tree.

Search in Leaf Node: Once you reach a leaf node, search for the key within the node. If the key is found, return the corresponding value or indicate that the key exists. If the key is not found, indicate that the key does not exist in the tree.
   
Follow Pointers: If the key is not found in the leaf node, follow any additional pointers based on the comparison with the keys in the node to continue the search process.
   
Complete Search: Repeat steps 2-4 until the key is found in a leaf node or until the search concludes that the key does not exist in the tree.

![image](https://github.com/CybersecurityDSA/B-Tree_KD-Tree/assets/144100792/edb330f0-2833-448b-b20c-8ee9fdd36a66)






