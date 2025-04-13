#ifndef REDBLACK_H
#define REDBLACK_H




enum Color { RED, BLACK };




struct RBNode 
{
    int key;
    enum Color color;
    struct RBNode *left, *right, *parent;
};



struct RBTree 
{
    struct RBNode *root;
};




//  Function for create tree
struct RBTree* create_tree();

//------------------------------------------------------------------------------

//  Function for create a node
struct RBNode* create_node(int key); 

//------------------------------------------------------------------------------

// Funcion for left rotate
void left_rotate(struct RBTree *tree, struct RBNode *x);

//------------------------------------------------------------------------------

//  Function for right rotate
void right_rotate(struct RBTree *tree, struct RBNode *y);


//------------------------------------------------------------------------------

//  Function for printing in order and formatted
void print_formatted(struct RBNode *node, int level);

//------------------------------------------------------------------------------

//  Function that inserts value into BST tree
void insert_BST(struct RBTree *tree, int key);

//------------------------------------------------------------------------------

//  Function to fix inclusion
void fix_inclusion(struct RBTree *tree, struct RBNode *z);

//------------------------------------------------------------------------------

//  Function that performs the transplant function on the tree
void RBTransplant(struct RBTree *tree, struct RBNode *u, struct RBNode *v);

//------------------------------------------------------------------------------

//  Function that finds the smallest value from the given node
struct RBNode *minimum(struct RBNode *node);

//------------------------------------------------------------------------------

//  Function that finds the largest value from the given node
struct RBNode *maximum(struct RBNode *node);

//------------------------------------------------------------------------------

//  Function that deletes a node
void delete(struct RBTree *tree, int key);

//------------------------------------------------------------------------------

//  Function that corrects the deletion of a node
void fix_deletion(struct RBTree *tree, struct RBNode *x);

//------------------------------------------------------------------------------

//  Function that destroys the created tree
void free_tree(struct RBNode *node);

//------------------------------------------------------------------------------

#endif