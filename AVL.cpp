#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int value;
	int height;
	Node* left, * right;
};
void init(Node*& root) {
	root = NULL;
}
int max(int a, int b) {
	return a > b ? a : b;
}
int getHeight(Node* root) {
	if (root == NULL)
		return 0;
	return root->height;
}
Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->left = p->right = NULL;
	p->height = 1;
	return p;
}
void rightRotate(Node*& root) {
	Node* x = root->left;
	root->left = x->right;
	x->right = root;
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	root = x;
}
void leftRotate(Node*& root) {
	Node* x = root->right;
	root->right = x->left;
	x->left = root;
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	root = x;
}
void addNode(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else {
		if (x > root->value)
			addNode(root->right, x);
		else if (x < root->value)
			addNode(root->left, x);
		else
			return;
		root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
		int balance = getHeight(root->left) - getHeight(root->right);
		if (balance > 1 && root->left->value > x)
			rightRotate(root);
		else if (balance < -1 && root->right->value < x)
			leftRotate(root);
		else if (balance > 1 && root->left->value < x) {
			leftRotate(root->left);
			rightRotate(root);
		}
		else if (balance < -1 && root->right->value > x) {
			rightRotate(root->right);
			leftRotate(root);
		}

	}
}
int getBalance(Node* root) {
	return getHeight(root->left) - getHeight(root->right);
}
void searchLeftFinal(Node*& p, Node*& q) {
	if (q->left == NULL) {
		p->value = q->value;
		p = q;
		q = q->right;
	}
	else {
		searchLeftFinal(p, q->left);
		if(q != NULL)
		  q->height = max(getHeight(q->left), getHeight(q->right)) + 1;
	}
}

void delNode(Node*& root, int x) {
	if (root == NULL)
		return;
	else if (root->value == x) {
		Node* p = root;
		if (root->left == NULL)
			root = root->right;
		else if (root->right == NULL)
			root = root->left;
		else
			searchLeftFinal(p, root->right);
		delete p;
		p = NULL;
	}
	else if (x > root->value)
		delNode(root->right, x);
	else if (x < root->value)
		delNode(root->left, x);
	if (root != NULL) {
		root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
		int balance = getHeight(root->left) - getHeight(root->right);
		if (balance > 1 && getBalance(root->left) >= 0)
			rightRotate(root);
		else if (balance < -1 && getBalance(root->right) <= 0)
			leftRotate(root);
		else if (balance > 1 && getBalance(root->left) < 0) {
			leftRotate(root->left);
			rightRotate(root);
		}
		else if (balance < -1 && getBalance(root->right) > 0) {
			rightRotate(root->right);
			leftRotate(root);
		}
	}
}
bool checkSNT(int n) {
	if (n < 2)
		return false;
	else {
		for (int i = 2; i <= sqrt(n); i++) {
			if (n % i == 0)
				return false;
		}
	}
	return true;
}
int countNodeSNT(Node* root) {
	if (root == NULL)
		return 0;
	if(checkSNT(root->value))
		return 1 + countNodeSNT(root->left) + countNodeSNT(root->right);
	return countNodeSNT(root->left) + countNodeSNT(root->right);
}
int countNode(Node* root) {
	if (root == NULL)
		return 0;
	return 1 + countNode(root->left) + countNode(root->right);
}
bool checkPerfectBinaryTree(Node* root) {
	if (root == NULL)
		return true;
	if (countNode(root->left) - countNode(root->right) == 0)
		return true;
	checkPerfectBinaryTree(root->left);
	checkPerfectBinaryTree(root->right);
	return false;
}
void display(Node* root) {
	queue<Node*> q;
	q.push(root);
	Node* p = NULL;
	while (!q.empty()) {
		p = q.front();
		cout << p->value << "(" << p->height << ") ";
		q.pop();
		if (p->left != NULL)
			q.push(p->left);
		if (p->right != NULL)
			q.push(p->right);
	}
}
void LNR(Node* root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->value << "(" << root->height << ") ";
		LNR(root->right);
	}
}



int main() {
	Node* root;
	init(root);
	addNode(root, 8);
	addNode(root, 3);
	addNode(root, 10);
	addNode(root, 2);
	addNode(root, 5);
	addNode(root, 9);
	addNode(root, 12);
	addNode(root, 1);
	addNode(root, 4);
	addNode(root, 6);
	addNode(root, 11);
	addNode(root, 7);
	delNode(root, 10);
	//res = 5(4) 3(3) 8(3) 2(2) 4(1) 6(2) 11(2) 1(1) 7(1) 9(1) 12(1)
	display(root);
	cout << endl;
	cout << countNodeSNT(root) << endl;
	/*cout << "\n=========================================\n";
	if (checkPerfectBinaryTree(root))
		cout << "PERFECT!\n";
	else
		cout << "NOT PERFECT!\n";*/
	return 1;
}