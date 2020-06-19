/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("---------------[������] [2019038023]---------------\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr) { //ptr�� NULL�� �ƴҶ����� ������ȸ ��
	inorderTraversal(ptr->left);
	printf("[%d] ", ptr->key);
	inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) { //ptr�� NULL�� �ƴҶ����� ������ȸ ��
	printf("[%d] ", ptr->key);
	preorderTraversal(ptr->left);
	preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) {//ptr�� NULL�� �ƴҶ����� ������ȸ ��
	postorderTraversal(ptr->left);
	postorderTraversal(ptr->right);
	printf("[%d]", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key; //�Է¹��� �� ���
	node->left = node->right = NULL;

	if (head->key == -9999) //ù��°�� ���� ����� ���
	{
		head->left = node;
		head->key = -8888;
		return 0;
	}

	Node* n = head->left;
	Node* p = NULL;

	while(n!=NULL){
		if(n->key>key){ //key�� ���� ��庸�� ������ �������� �̵�
			p=n;
			n=n->left;
		}
		else if (n->key<key){ //key�� ���� ��庸�� ������ ���������� �̵�
			p=n;
			n=n->right;
		}
		else
			return 0;
	}

	if(p->key>key)  /*key�� ������ ���ʿ� ũ�� �����ʿ� �־���*/
		p->left=node;

	else if(p->key<key)
		p->right=node;

	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* tree=head->left;
	Node* trail;

	while (tree) {
		if(key == tree->key && tree->left == NULL && tree->right == NULL) //key�� node�� key�� ���� ��� while�� ���´�.
			break;

		else if(key == tree->key && (tree->left != NULL || tree->right != NULL)){ //key�� node�� key�� ������ leaf��� �� ��� ������.
			printf("[%d] is not a leaf node.", key);
			return 1;
		}
		if (key < tree->key){ //key�� node���� ���� ���
			trail=tree;
			tree = tree->left;
		}
		else{ //key�� node���� Ŭ ���
			trail=tree;
			tree = tree->right;
		}
	}

	if (key == tree->key) { //key�� ����� key�� ���� ��� �θ����� left�� right�� null�� �ٲ���
		if(trail->right==tree)
			trail->right=NULL;
		else
			trail->left=NULL;
		free(tree);
		return 0;
	}

	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (!ptr) return NULL; //ptr�� null�� ��� null�� ��ȯ
	if (key == ptr->key) return ptr; //key�� ptr�� key�� ������ ptr�� ��ȯ
	if (key < ptr->key) //key�� ������� left�� key��, Ŭ��� right�� key�� ��ȯ
		return searchRecursive(ptr->left, key);
	return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	Node* tree=head->left;
	while (tree) {
	if (key == tree->key) return tree; //tree�� key�� key�� ������ tree��ȯ

	if (key < tree->key) //key�� tree�� key���� ������  left��, ũ�� right�� ��ȯ
		tree = tree->left;
	else
		tree = tree->right;
	}

	return NULL;
}


int freeBST(Node* head)
{
	Node*ptr=head->left;

	if (ptr) { //ptr�� NULL�� �ƴҶ�����
		freeBST(ptr);
		free(ptr);
		}
}




