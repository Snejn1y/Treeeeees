## AVL and Red-Black Tree

This code implements AVL and Red-Black trees in C++. The program allows you to perform various operations on the trees, including insertion, deletion, and tree traversal. Additionally, there are options to generate random trees and analyze the performance of the algorithms.

### AVL Tree Functions

- `void add(avl_tree& avl_tr, const int& data)`: Adds a new node with the given data to the AVL tree.
- `void del(avl_tree& avl_tr, const int& data)`: Removes the node with the given data from the AVL tree.
- `void postfix(elem* top)`: Performs a postfix traversal of the AVL tree.
- `void prefix(elem* top)`: Performs a prefix traversal of the AVL tree.
- `void infix(elem* top)`: Performs an infix traversal of the AVL tree.
- `void inputTree(avl_tree& tree, int n)`: Allows you to input a specific number of elements to create an AVL tree.
- `void randTree(avl_tree& tree, int n)`: Generates a random AVL tree with a specified number of nodes.
- `void remove_r(avl_tree& avl_tr, const int& r)`: Removes all nodes from the AVL tree that have a value smaller than or equal to `r`.
- `void delete_avl_nodes(elem* node)`: Deletes all nodes in the AVL tree recursively.

### Red-Black Tree Functions

- `bool rb_insert(rb_tree* tree, int data)`: Inserts a new node with the given data into the Red-Black tree.
- `bool rb_remove(rb_tree* tree, int data)`: Removes the node with the given data from the Red-Black tree.
- `void postfix(rb_node* top)`: Performs a postfix traversal of the Red-Black tree.
- `void prefix(rb_node* top)`: Performs a prefix traversal of the Red-Black tree.
- `void infix(rb_node* top)`: Performs an infix traversal of the Red-Black tree.
- `void inputTree(rb_tree& tree, int n)`: Allows you to input a specific number of elements to create a Red-Black tree.
- `void randTree(rb_tree& tree, int n)`: Generates a random Red-Black tree with a specified number of nodes.
- `void remove_r(rb_tree& tree, int r)`: Removes all nodes from the Red-Black tree that have a value smaller than or equal to `r`.
- `void delete_rb_nodes(rb_node* node)`: Deletes all nodes in the Red-Black tree recursively.

### Other Functions

- `void Ftest()`: Performs a test on AVL trees by generating trees with increasing numbers of nodes and measuring the time taken for removal operations.
- `void Stest()`: Performs a test on Red-Black trees by generating trees with increasing numbers of nodes and measuring the time taken for removal operations.
- `void Show()`: Demonstrates example AVL and Red-Black trees by performing various operations and displaying the resulting trees.
- `int main()`: The main function provides a user interface for interacting with AVL and Red-Black trees.

Feel free to use this code as a reference for implementing AVL and Red-Black trees or experimenting with different operations on trees.
