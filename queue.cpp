#include <iostream>

#define MAX 5
using namespace std;

struct Node {
	int x;
	int prior;
};

struct Queue {
	Node a[MAX];
	int front, rear;
};

void init(Queue& q) {
	q.front = q.rear = -1;
}

bool isEmpty(Queue q) {
	return q.front > q.rear;
}
void enQueue(Queue& q, Node x) {
	if (q.rear - q.front == MAX - 1)
		return;
	if (q.front == -1) {
		q.a[0] = x;
		q.front = q.rear = 0;
	}
	else {
		//x li tran
		if (q.rear == MAX - 1) {
			for (int i = q.front; i <= q.rear; i++) {
				q.a[i - 1] = q.a[i];
			}
			q.rear -= q.front;
			q.front = 0;
		}

		int i;
		for (i = q.rear; i >= q.front; i--) {
			if (x.prior > q.a[i].prior)
				q.a[i + 1] = q.a[i];
			else
				break;
		}

		q.a[i + 1] = x;
		q.rear++;
	}
}

Node* deQueue(Queue& q) {
	if (q.front == -1)
		return NULL;
	Node* tmp = &q.a[q.front];
	if (q.front > q.rear)
		return NULL;
	q.front++;
	return tmp;
}

void Push(Queue& q, Node x)
{
	if (q.rear - q.front == MAX - 1 || q.rear - q.front == -1)
		return ;
	else
	{
		if (q.front == -1) // xét hang đợi rỗng
			q.front = 0; // khi đó rear =-1;
		if (q.rear == MAX - 1) // hang đợi bị tràn
			q.rear = -1; // hang đợi tràn, vòng giá trị rear xuống -1
		q.a[++q.rear] = x; // tang rear lên 1 giá trị, và thêm phần tử mới tại
	}
}
Node* Pop(Queue& q) {
	if (q.front != -1) {
		Node* x = &q.a[q.front];
		if (q.front == q.rear)
		{
			q.front = -1;
			q.rear = -1;
		}
		else
		{
			q.front++;
			if (q.front > MAX - 1) 
				q.front = 0;
		}
		return x;
	} return NULL;
}
void output(Queue& q) {
	while (!isEmpty(q)) {
		Node* tmp = deQueue(q);
		cout << tmp->x << "-" << tmp->prior << endl;
	}
}
void newOutput(Queue& q) {
	while (q.rear != -1) {
		Node* tmp = Pop(q);
		cout << tmp->x << "-" << tmp->prior << endl;
	}
}
int main() {
	Queue(q);
	init(q);
	Node n1, n2, n3, n4, n5, n6;
	n1.x = 1;
	n1.prior = 1;
	n2.x = 2;
	n2.prior = 1;
	n3.x = 3;
	n3.prior = 1;
	n4.x = 4;
	n4.prior = 2;
	n5.x = 5;
	n5.prior = 3;
	Push(q, n1);
	Push(q, n2);
	Push(q, n3);
	Push(q, n4);
	Push(q, n5);
	cout << Pop(q)->x << endl;
	/*deQueue(q);
	enQueue(q, 6);*/
	n6.x = 1000;
	n6.prior = 1000;
	Push(q, n6);
	/*deQueue(q);
	n6.x = 1000;
	n6.prior = 1000;
	enQueue(q, n6);*/
	newOutput(q);
	return 1;
}