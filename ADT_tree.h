#ifndef ADT_TREE
#define ADT_TREE
#include <stdio.h>
#include <stdlib.h>

// Tree Node
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
} T_NODE;

// TREE
typedef struct {
	int count;
	T_NODE* root;
} BST_TREE;

// Operations;
BST_TREE* create_bst_tree();//ok
T_NODE* find_smallest_node(T_NODE* root);//ok
T_NODE* find_largest_node(T_NODE* root);//ok
T_NODE* search_bst(T_NODE* root, int key);//ok
T_NODE* add_bst(T_NODE* root, int data);//ok
T_NODE* delete_bst(T_NODE* root, int data, bool* success);

void traverse_preorder(T_NODE* root);
void traverse_inorder(T_NODE* root);
void traverse_postorder(T_NODE* root);

bool BST_insert(BST_TREE* tree, int data);
bool BST_delete(BST_TREE* tree, int data);
void BST_print(BST_TREE* tree, int method);//ok
bool BST_destroy(BST_TREE* tree);

#endif
