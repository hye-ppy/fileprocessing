#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)
typedef struct treeNode {
	int data;
	struct treeNode *leftNode;
	struct treeNode *rightNode;
}treeNode;
//treeNode *root = NULL;
int stop = 0;
void plus()
{
	stop++;
}

treeNode *LL(treeNode *p) {
	treeNode *child;

	child = p->leftNode;
	p->leftNode = child->rightNode;
	child->rightNode = p;
	return child;
}
treeNode *RR(treeNode *p) {
	treeNode *child;

	child = p->rightNode;
	p->rightNode = child->leftNode;
	child->leftNode = p;
	return child;
}
treeNode *LR(treeNode *p) {
	treeNode *child;

	child = p->leftNode;
	p->leftNode = RR(child);
	return LL(p);
}
treeNode *RL(treeNode *p) {
	treeNode *child;

	child = p->rightNode;
	p->rightNode = LL(child);
	return RR(p);
}
int getHeight(treeNode *node) {
	int height;

	height = 0;
	if (node != NULL) {
		//height = 1 + max(getHeight(node->leftNode), getHeight(node->rightNode));
		int x = getHeight(node->leftNode);
		int y = getHeight(node->rightNode);
		if ( x > y ) {
			height = 1 + x;
		}
		else {
			height = 1 + y;
		}
	}
		return height;
}
int getBalance(treeNode *node) {
	if (node == NULL) return 0;
	return getHeight(node->leftNode) - getHeight(node->rightNode);
}
treeNode *treeBalance(treeNode **node) {
	int height;
	height = getBalance(*node);
	if (height > 1) {
		if (getBalance((*node)->leftNode) > 0) {
			*node = LL(*node);
		}
		else {
			*node = LR(*node);
		}
	}
	else if (height < -1) {
		if (getBalance((*node)->rightNode) < 0) {
			*node = RR(*node);
		}
		else {
			*node = RL(*node);
		}
	}
	return *node;
}
treeNode *treeBalance2(treeNode **node) {
	int height;
	height = getBalance(*node);
	if (height > 1) {
		if (getBalance((*node)->leftNode) > 0) {
			*node = LL(*node);
		}
		else {
			*node = LR(*node);
		}
		plus();
	}
	else if (height < -1) {
		if (getBalance((*node)->rightNode) < 0) {
			*node = RR(*node);
		}
		else {
			*node = RL(*node);
		}
		plus();
	}

	return *node;
}

treeNode *insertAVL(treeNode **root, int data) {
	if (*root == NULL) {
		*root = (treeNode*)malloc(sizeof(treeNode));
		(*root)->data = data;
		(*root)->leftNode = NULL;
		(*root)->rightNode = NULL;
	}
	else if ((*root)->data > data) {
		(*root)->leftNode = insertAVL(&((*root)->leftNode), data);
		*root = treeBalance(root);
	}
	else if ((*root)->data < data) {
		(*root)->rightNode = insertAVL(&((*root)->rightNode), data);
		*root = treeBalance(root);
	}
	return *root;
}
treeNode *searchTree(treeNode *root, int data) {
	treeNode *p;
	int count = 0;
	p = root;
	while (p != NULL) {
		count++;
		if (data < p->data)p = p->leftNode;
		else if (data == p->data) {
			//¼º°ø
			return p;
		}
		else p = p->rightNode;
	}
	count++;
	return p;
}
void preorder(treeNode *root,FILE *output) {
	if (root != NULL) {
		fprintf(output,"%d ",root->data);
		preorder(root->leftNode, output);
		preorder(root->rightNode, output);
	}
}
treeNode* delBalance(treeNode **root) {
	if (*root != NULL) {
		*root=treeBalance2(root);
		delBalance(&((*root)->leftNode));
		delBalance(&((*root)->rightNode));
	}
}
void delNode(treeNode *root, int data) {
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;
	parent = NULL;
	p = root;
	while ((p != NULL) && (p->data != data)) {
		parent = p;
		if (data < p->data) {
			p = p->leftNode;
		}
		else {
			p = p->rightNode;
		}
	}
	if (p == NULL) return;
	if ((p->leftNode == NULL) && (p->rightNode == NULL)) {
		if (parent != NULL) {
			if (parent->leftNode == p) {
				parent->leftNode = NULL;
			}
			else {
				parent->rightNode = NULL;
			}
		}
		else root = NULL;
	}
	else if ((p->leftNode == NULL) || (p->rightNode == NULL)) {
		if (p->leftNode != NULL) {
			child = p->leftNode;
		}
		else {
			child = p->rightNode;
		}
		if (parent != NULL) {
			if (parent->leftNode == p) {
				parent->leftNode = child;
			}
			else {
				parent->rightNode = child;
			}
		}
		else root = child;
	}
	else {
		succ_parent = p;
		succ = p->leftNode;
		while (succ->rightNode != NULL) {
			succ_parent = succ;
			succ = succ->rightNode;
		}
		if (succ_parent->leftNode == succ) {
			succ_parent->leftNode = succ->leftNode;
		}
		else {
			succ_parent->rightNode = succ->leftNode;
		}
		
		p->data = succ->data;
		p = succ;
	}
	//treeBalance(&root);
	free(p);
}
int main() {
	FILE *input, *output;

	input = fopen("hw4.inp", "rt");
	output = fopen("hw4.out", "wt");

	int a;
	char b;
	treeNode *root = NULL;

	for (int i = 0;; i++) {
		fscanf(input, "%d%c", &a, &b);
		insertAVL(&root, a);
		
		if (b == '\n') break;
	}
	preorder(root, output);
	fprintf(output, "\n");

	for (int i = 0;; i++) {
		fscanf(input, "%d%c", &a, &b);
		delNode(root, a);
		//stop = 0;
		delBalance(&root);
		//treeBalance(&root);
		if (b == '\n') break;
	}
	preorder(root, output);
	fprintf(output, "\n*");

	fclose(input);
	fclose(output);
}