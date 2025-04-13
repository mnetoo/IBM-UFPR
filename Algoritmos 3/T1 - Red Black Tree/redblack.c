#include <stdio.h>
#include <stdlib.h>
#include "redblack.h"











//  Function for create tree
struct RBTree* create_tree() 
{
    struct RBTree* tree = (struct RBTree*)malloc(sizeof(struct RBTree));
    tree->root = NULL;

    return tree;
}


//------------------------------------------------------------------------------


//  Function for create a node
struct RBNode* create_node(int key) 
{
    struct RBNode* node = (struct RBNode*)malloc(sizeof(struct RBNode));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NULL;

    return node;
}


//------------------------------------------------------------------------------


// Funcion for left rotate
void left_rotate(struct RBTree *tree, struct RBNode *x) 
{
    struct RBNode *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}


//------------------------------------------------------------------------------


//  Function for right rotate
void right_rotate(struct RBTree *tree, struct RBNode *x) 
{
    struct RBNode *l = x->left;
    x->left = l->right;

    if (l->right != NULL)
        l->right->parent = x;

    l->parent = x->parent;

    if (x->parent == NULL)
        tree->root = l;
    else if (x == x->parent->right)
        x->parent->right = l;
    else
        x->parent->left = l;

    l->right = x;
    x->parent = l;
}


//------------------------------------------------------------------------------


//  Function for printing in order and formatted
void print_formatted(struct RBNode *node, int level) 
{
    if (node == NULL) 
        return;

    print_formatted(node->left, level + 1);
    printf("%d,%d,%d\n", node->key, level, node->color == RED ? 1 : 0);
    print_formatted(node->right, level + 1);
}


//-------------------------------------------------


//  Function that inserts value into BST tree
void insert_BST(struct RBTree *tree, int key) 
{
    struct RBNode *new_node = create_node(key);
    struct RBNode *y = NULL;
    struct RBNode *x = tree->root;

    while (x != NULL) 
    {
        y = x;
        if (new_node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    new_node->parent = y;

    if (y == NULL)
        tree->root = new_node;
    else if (new_node->key < y->key)
        y->left = new_node;
    else
        y->right = new_node;

    fix_inclusion(tree, new_node);
}


//------------------------------------------------------------------------------


//  Function to fix inclusion
void fix_inclusion(struct RBTree *tree, struct RBNode *z) 
{
    while (z->parent != NULL && z->parent->color == RED) 
    {
        struct RBNode *pai = z->parent;
        struct RBNode *avo = pai->parent;

        if (pai == avo->left) 
        {
            struct RBNode *tio = avo->right;

            if (tio != NULL && tio->color == RED) 
            {
                pai->color = BLACK;
                tio->color = BLACK;
                avo->color = RED;
                z = avo;
            } 
            else 
            {
                if (z == pai->right) 
                {
                    z = pai;
                    left_rotate(tree, z);
                    pai = z->parent;
                }
                pai->color = BLACK;
                avo->color = RED;
                right_rotate(tree, avo);
            }
        } 
        else 
        {
            struct RBNode *tio = avo->left;

            if (tio != NULL && tio->color == RED) 
            {
                pai->color = BLACK;
                tio->color = BLACK;
                avo->color = RED;
                z = avo;
            } 
            else 
            {
                if (z == pai->left) 
                {
                    z = pai;
                    right_rotate(tree, z);
                    pai = z->parent;
                }
                pai->color = BLACK;
                avo->color = RED;
                left_rotate(tree, avo);
            }
        }
    }

    tree->root->color = BLACK;
}


//------------------------------------------------------------------------------


//  Function that performs the transplant function on the tree
void RBTransplant(struct RBTree *tree, struct RBNode *u, struct RBNode *v) 
{
    if (u->parent == NULL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}


//------------------------------------------------------------------------------


//  Function that finds the smallest value from the given node
struct RBNode *minimum(struct RBNode *node) 
{
    while (node->left != NULL)
        node = node->left;
    return node;
}


//------------------------------------------------------------------------------


//  Function that finds the largest value from the given node
struct RBNode *maximum(struct RBNode *node) 
{
    while (node->right != NULL)
        node = node->right;
    return node;
}


//------------------------------------------------------------------------------


//  Function that deletes a node
void delete(struct RBTree *tree, int key) 
{
    struct RBNode *z = tree->root;

    // Busca o nó a ser removido
    while (z != NULL && z->key != key) 
    {
        if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL)
        return; // O nó não foi encontrado

    struct RBNode *y = z;
    enum Color y_original_color = y->color;
    struct RBNode *x;

    if (z->left == NULL) 
    {
        x = z->right;
        RBTransplant(tree, z, z->right);
    } 
    else if (z->right == NULL) 
    {
        x = z->left;
        RBTransplant(tree, z, z->left);
    } 
    else 
    {
        // Usamos o antecessor (máximo da subárvore esquerda) para remoção
        y = maximum(z->left);  // Encontrando o antecessor (máximo da subárvore esquerda)
        y_original_color = y->color;
        x = y->left;  // O filho esquerdo de y (se houver)

        if (y->parent == z) 
        {
            // Caso especial: o antecessor está diretamente à esquerda de z
            if (x != NULL)
                x->parent = y;
        } 
        else 
        {
            // Transplantar y para a posição de y
            RBTransplant(tree, y, y->left);
            y->left = z->left;
            if (y->left != NULL)
                y->left->parent = y;
        }

        // Transplanta y para o lugar de z
        RBTransplant(tree, z, y);
        y->right = z->right;
        if (y->right != NULL)
            y->right->parent = y;
        y->color = z->color;
    }

    free(z);  // Libera o nó removido

    // Se a cor original de y era preta, precisamos corrigir o balanceamento da árvore
    if (y_original_color == BLACK && x != NULL)
        fix_deletion(tree, x);
}


//------------------------------------------------------------------------------


//  Function that corrects the deletion of a node
void fix_deletion(struct RBTree *tree, struct RBNode *x) 
{
    while (x != tree->root && (x == NULL || x->color == BLACK)) 
    {
        struct RBNode *w;
        if (x == x->parent->left) 
        {
            w = x->parent->right;

            if (w != NULL && w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }

            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) 
            {
                w->color = RED;
                x = x->parent;
            } 
            else 
            {
                if (w->right == NULL || w->right->color == BLACK) 
                {
                    if (w->left != NULL)
                        w->left->color = BLACK;

                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;

                if (w->right != NULL)
                    w->right->color = BLACK;

                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } 
        else 
        {
            w = x->parent->left;

            if (w != NULL && w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }

            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) 
            {
                w->color = RED;
                x = x->parent;
            }
            else 
            {
                if (w->left == NULL || w->left->color == BLACK) 
                {
                    if (w->right != NULL)
                        w->right->color = BLACK;

                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;

                if (w->left != NULL)
                    w->left->color = BLACK;

                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}


//------------------------------------------------------------------------------


//  Function that destroys the created tree
void free_tree(struct RBNode *node) 
{
    if (node == NULL)
        return;

    // Libera a subárvore esquerda
    free_tree(node->left);

    // Libera a subárvore direita
    free_tree(node->right);

    // Libera o próprio nó
    free(node);
}


//------------------------------------------------------------------------------