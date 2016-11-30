#include "ADT_tree.h"

BST_TREE* create_bst_tree() {
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	tree->count = 0;
	tree->root = NULL;
	return tree;
}

T_NODE* find_smallest_node(T_NODE* root) {
	if(root->left == NULL)
		return root;
	else
		return find_smallest_node(root->left);
}

T_NODE* find_largest_node(T_NODE* root) {
	if(root->right == NULL)
		return root;
	else
		return find_largest_node(root->right);
}

T_NODE* search_bst(T_NODE* root, int key) {
	if(root==NULL) return NULL;
	if(key < root->data)
		return search_bst(root->left, key);
	else if(key > root->data)
		return search_bst(root->right,key);
	else
		return root;
}

T_NODE* add_bst(T_NODE* root, int data) {
	if(root == NULL) {
		T_NODE* newPtr =  (T_NODE*)malloc(sizeof(T_NODE));
		newPtr->right = NULL;
		newPtr->left = NULL;
		newPtr->data = data;
	return newPtr;
	}
	if(data < root->data) {
		root->left = add_bst(root->left,data);
		return root;
	}
	else {
		root->right = add_bst(root->right,data);
		return root;
	}
}

T_NODE* delete_bst(T_NODE* root, int data, bool* success) {
	if(root == NULL) {
		*success = false;
		return NULL;
	}
	//traverse
	if(data < root->data)
		root->left = delete_bst(root->left, data, success);
	else if(data > root->data)
		root->right = delete_bst(root->right, data, success);
	else { //matched
		T_NODE* deleted_node = root;//backup
		if(root->left == NULL) {
			T_NODE* newRoot = root->right;
			free(deleted_node);
			*success = true;
			return newRoot;
		} else if(root->right == NULL) {
			T_NODE* newRoot = root->left;
			free(deleted_node);
			*success = true;
			return newRoot;
		} else {
			T_NODE* search = root->left;
			while(search->right != NULL)
				search = search->right;
			root->data = search->data;
			root->left = delete_bst(root->left, search->data, success);
		}
	}
	return root;
}

bool BST_insert(BST_TREE* tree, int data) {
	T_NODE* newRoot = add_bst(tree->root,data);
	if(newRoot ==NULL) return false;
	else {
		tree->root = newRoot;
		(tree->count)++;
		return true;
	}
}

bool BST_delete(BST_TREE* tree, int data) {
	bool success;
	T_NODE* newRoot;
	newRoot = delete_bst(tree->root, data, &success);
	if(success) {
		tree->root = newRoot;
		(tree->count)--;
		if(tree->count == 0)
			tree->root = NULL;
	}
	return success;
}

void traverse_preorder(T_NODE* root) {
	if(root) {
		printf("%d,",root->data);
		traverse_preorder(root->left);
		traverse_preorder(root->right);
	}
	return;
}

void traverse_postorder(T_NODE* root) {
	if(root) {
		traverse_postorder(root->left);
		traverse_postorder(root->right);
		printf("%d,",root->data);
	}
	return;
}

void traverse_inorder(T_NODE* root) {
	if(root) {
		if(root->left != NULL)
			traverse_inorder(root->left);
		printf("%d,",root->data);
		if(root->right != NULL)
			traverse_inorder(root->right);
	}
	return;
}

void BST_print(BST_TREE* tree, int method) {
	printf("BST_TREE:\n");
	printf(" size : %d\n", tree->count);
	printf(" data : ");

	if(method == 0)
		traverse_preorder(tree->root);
	else if(method == 1)
		traverse_inorder(tree->root);
	else if(method ==2)
		traverse_postorder(tree->root);
	else
		printf("type error");

	printf("\n");
}

bool BST_destroy(BST_TREE* tree) {
	while(tree->count !=0) {
	int min = (find_smallest_node(tree->root))->data;
	if(!BST_delete(tree,min))
		printf("failed on deleting min.node : %d\n",min);
	//printf("deleted node: %d\n", min);
	//printf("current nodes in tree : %d\n",tree->count);
	}
	free(tree);

}
