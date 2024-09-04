#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#define MAX 100
using namespace std;
struct Node {
	int value;
	Node* left;
	Node* right;
};

void init(Node*& root) {
	root = NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->left = p->right = NULL;
	return p;
}
void addNode(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	if (x == root->value)
		return;
	if (x > root->value)
		addNode(root->right, x);
	else if (x < root->value)
		addNode(root->left, x);

}

void searchLeftNode(Node*& p, Node*& q) {
	if (q->left == NULL) {
		p->value = q->value;
		p = q;
		q = q->right;
	}
	else
		searchLeftNode(p, q->left);
}
void delNode(Node*& root, int x) {
	if (root == NULL)
		return;
	if (x == root->value) {
		Node* p = root;
		if (root->right == NULL)
			root = root->left;
		else if (root->left == NULL)
			root = root->right;
		else {
			searchLeftNode(p, root->right);
		}
		delete p;
		p = NULL;
		return;
	}
	if (x > root->value)
		delNode(root->right, x);
	else if (x < root->value)
		delNode(root->left, x);
}
struct Stack {
	Node* a[MAX];
	int top;
};
void init(Stack& s) {
	s.top = -1;
}
void push(Stack& s, Node* x) {
	s.a[++s.top] = x;
}
Node* geek(Stack s) {
	return s.a[s.top];
}
void pop(Stack& s) {
	s.a[s.top--];
}
bool isEmpty(Stack s) {
	return s.top == -1;
}
struct NodeQueue {
	Node* value;
	NodeQueue* next;
};
void init(NodeQueue*& q) {
	q = NULL;
}
bool isEmpty(NodeQueue* q) {
	return q == NULL;
}
NodeQueue* createNodeQueue(Node* x) {
	NodeQueue* p = new NodeQueue;
	p->value = x;
	p->next = NULL;
	return p;
}
void enQueue(NodeQueue*& head, Node* x) {
	if (head == NULL)
		head = createNodeQueue(x);
	else {
		NodeQueue* p = createNodeQueue(x);
		NodeQueue* q = head;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = p;
	}
}
Node* deQueue(NodeQueue*& head) {
	if (head != NULL) {
		NodeQueue* p = head;
		head = head->next;
		p->next = NULL;
		return p->value;
	}
}
void LNR(Node* root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->value << " ";
		LNR(root->right);
	}
}
void LRN(Node* root) {
	if (root != NULL) {
		LRN(root->left);
		LRN(root->right);
		cout << root->value << " ";
	}
}
void NLR(Node* root) {
	if (root != NULL) {
		cout << root->value << " ";
		NLR(root->left);
		NLR(root->right);
	}
}
void lnrNoRecursion(Node* root) {
	Stack s;
	init(s);
	Node* cur = root;
	while (cur != NULL || !isEmpty(s)) {
		if (cur != NULL) {
			push(s, cur);
			cur = cur->left;
		}
		else {
			cout << geek(s)->value << " ";
			cur = geek(s)->right;
			pop(s);
		}
	}
}
void lrn2Stack(Node* root) {
	Stack s1, s2;
	init(s1);
	init(s2);
	push(s1, root);
	while (!isEmpty(s1)) {
		Node* cur = geek(s1);
		pop(s1);
		push(s2, cur);
		if (cur->left != NULL)
			push(s1, cur->left);
		if (cur->right != NULL)
			push(s1, cur->right);
	}
	while (!isEmpty(s2)) {
		cout << geek(s2)->value << " ";
		pop(s2);
	}
}
void lrn1Stack(Node* root) {
	Stack s;
	init(s);
	Node* cur = root;
	while (true) {
		if (cur != NULL) {
			push(s, cur);
			cur = cur->left;
		}
		else {
			if (isEmpty(s))
				break;
			if (geek(s)->right == NULL) {
				cout << geek(s)->value << " ";
				cur = geek(s);
				pop(s);
				while (geek(s)->right == cur) {
					cout << geek(s)->value << " ";
					cur = geek(s);
					pop(s);
					if (isEmpty(s))
						break;
				}
			}
			if (!isEmpty(s))
				cur = geek(s)->right;
			else
				cur = NULL;
		}
	}
}
void nlrNoRecursion(Node* root) {
	Stack s;
	init(s);
	push(s, root);
	Node* cur = NULL;
	while (!isEmpty(s)) {
		cur = geek(s);
		cout << cur->value << " ";
		pop(s);
		if (cur->right != NULL)
			push(s, cur->right);
		if (cur->left != NULL)
			push(s, cur->left);
	}
}
void displayTreeQueue(Node* root) {
	NodeQueue* q;
	init(q);
	enQueue(q, root);
	Node* cur = NULL;
	while (!isEmpty(q)) {
		cur = deQueue(q);
		cout << cur->value << " ";
		if (cur->left != NULL)
			enQueue(q, cur->left);
		if (cur->right != NULL)
			enQueue(q, cur->right);
	}
}


int main()
{


	return 0;
}