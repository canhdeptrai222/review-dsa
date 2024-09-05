#include <iostream>

using namespace std;

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
struct Node {
	int value;
	int point;
	Node* next;
};
struct CircularLinkedList {
	Node* head;
	Node* tail;
};
void init(CircularLinkedList& ls) {
	ls.head = ls.tail = NULL;
}
Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->point = 0;
	p->next = NULL;
	return p;
}
void addLast(CircularLinkedList& ls, int x) {
	if (ls.head == NULL) {
		ls.head = ls.tail = createNode(x);
		ls.tail->next = ls.head;
	}
	else {
		Node* p = createNode(x);
		p->next = ls.head;
		ls.tail->next = p;
		ls.tail = p;
	}
}
void delLast(CircularLinkedList& ls) {
	if (ls.head != NULL) {
		Node* p = ls.head;
		if (ls.head == ls.tail)
			ls.head = ls.tail = NULL;
		else {
			Node* prev = NULL;
			do {
				prev = p;
				p = p->next;
			} while (p != ls.tail);
			prev->next = p->next;
			p->next = NULL;
			ls.tail = prev;
		}
		delete p;
		p = NULL;
	}
}
void delNode(CircularLinkedList& ls, int x) {
	if (ls.head != NULL) {
		Node* p = ls.head;
		if (ls.head == ls.tail)
			ls.head = ls.tail = NULL;
		else {
			Node* prev = NULL;
			do {
				if (p->value == x)
					break;
				prev = p;
				p = p->next;
			} while (p != ls.tail->next);
			if (prev == NULL) {
				ls.head = ls.head->next;
				ls.tail->next = ls.head;
				p->next = NULL;
			}
			else if (prev->next == ls.tail) {
				prev->next = p->next;
				p->next = NULL;
				ls.tail = prev;
			}
			else {
				prev->next = p->next;
				p->next = NULL;
			}
		}
		delete p;
		p = NULL;
	}
}
void display(CircularLinkedList& ls) {
	if (ls.head != NULL) {
		Node* p = ls.head;
		do {
			cout << p->value << " ";
			p = p->next;
		} while (p != ls.tail->next);
	}
}
Node* search(CircularLinkedList ls, int x) {
	if (ls.head != NULL) {
		Node* p = ls.head;
		do {
			if (p->value == x)
				return p;
			p = p->next;
		} while (p != ls.tail->next);
	}
}
void createCircle(CircularLinkedList& ls, int n) {
	for (int i = 0; i < n; i++){
		addLast(ls, i + 1);
	}
}
void play(CircularLinkedList& ls, int n) {
	createCircle(ls, n);
	//display(ls);
	/*cout << "\nChon vi tri bat dau: ";*/
	/*int index;
	cin >> index;*/
	/*cout << endl;*/
	Node* p = search(ls, 1);
	while (ls.head != ls.tail) {
		for (int i = 1; i <= n; i++) {
			if (checkSNT(i)) {
				Node* tmp = p;
				//cout << p->value << " ";
				p = p->next;
				delNode(ls, tmp->value);
			}
			else
				p = p->next;
			if (ls.head == ls.tail)
				break;
		}
	}
	cout << "\nNguoi chien thang : " << ls.head->value << endl;
	ls.head = ls.tail = NULL;
	delete ls.head;
}

int main() {
	CircularLinkedList ls;
	init(ls);
	play(ls, 41);
	return 1;
}