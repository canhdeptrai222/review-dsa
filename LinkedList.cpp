#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <ctime>
#define MAXCHOICE 8
#define DIEMTB 3
using namespace std;

struct SinhVien {
	long long mssv;
	string hoTen;
	char maLop[9];
	string queQuan;
	char ngaySinh[11];
	string phoneNumber;
	double diemTB[3];
};
void nhapTT1SV(SinhVien& sv) {
	cout << "Nhap mssv: ";
	cin >> sv.mssv;
	cin.ignore();
	cout << "Nhap ho ten: ";
	getline(cin, sv.hoTen);
	cout << "Nhap ma lop: ";
	cin >> sv.maLop;
	cin.ignore();
	cout << "Nhap que quan: ";
	getline(cin, sv.queQuan);
	cout << "Nhap ngay sinh: ";
	cin >> sv.ngaySinh;
	cout << "Nhap so dien thoai: ";
	cin >> sv.phoneNumber;
	cout << "Nhap diem trung binh 3 mon: ";
	for (int i = 0; i < DIEMTB; i++) {
		cin >> sv.diemTB[i];
	}
}
void xuatTT1SV(const SinhVien sv) {
	cout << "===========THONG TIN SINH VIEN===========\n";
	cout << "MSSV: " << sv.mssv << endl;
	cout << "Ho va ten: " << sv.hoTen << endl;
	cout << "Ma lop: " << sv.maLop << endl;
	cout << "Que quan: " << sv.queQuan << endl;
	cout << "Ngay sinh: " << sv.ngaySinh << endl;
	cout << "So dien thoai: " << sv.phoneNumber << endl;
	cout << "Diem trung binh 3 mon: ";
	for (int i = 0; i < DIEMTB; i++) {
		cout << sv.diemTB[i] << " ";
	}
	cout << "\n========================================\n\n";
}
struct NodeSinhVien {
	SinhVien sv;
	NodeSinhVien* next;
	NodeSinhVien* prev;
};
struct DoublyLinkedList {
	NodeSinhVien* head;
	NodeSinhVien* tail;
};
void init(DoublyLinkedList& ls) {
	ls.head = ls.tail = NULL;
}
NodeSinhVien* createNode(SinhVien sv) {
	NodeSinhVien* p = new NodeSinhVien;
	p->sv = sv;
	p->next = p->prev = NULL;
	return p;
}
void addFirst(DoublyLinkedList& ls, SinhVien sv) {
	if (ls.head == NULL)
		ls.head = ls.tail = createNode(sv);
	else {
		NodeSinhVien* p = createNode(sv);
		p->next = ls.head;
		ls.head->prev = p;
		ls.head = p;
	}
}
void addLast(DoublyLinkedList& ls, SinhVien sv) {
	if (ls.tail == NULL)
		ls.head = ls.tail = createNode(sv);
	else {
		NodeSinhVien* p = createNode(sv);
		ls.tail->next = p;
		p->prev = ls.tail;
		ls.tail = p;
	}
}
void addNodeOrderList(DoublyLinkedList& ls, SinhVien sv) {
	if (ls.head == NULL) {
		ls.head = ls.tail = createNode(sv);
	}
	else {
		NodeSinhVien* q = ls.head;
		NodeSinhVien* p = createNode(sv);
		if (p->sv.mssv < q->sv.mssv) {
			p->next = ls.head;
			ls.head->prev = p;
			ls.head = p;
		}
		else {
			NodeSinhVien* prev = NULL;
			while (q != NULL && p->sv.mssv > q->sv.mssv) {
				prev = q;
				q = q->next;
			}
			if (q == NULL) {
				prev->next = p;
				p->prev = prev;
			}
			else if(prev != NULL) {
				p->next = q;
				q->prev = p;
				prev->next = p;
				p->prev = prev;
			}
		}
		
	}
}
void delFirst(DoublyLinkedList& ls) {
	if (ls.head != NULL) {
		NodeSinhVien* p = ls.head;
		if (ls.head->next == NULL)
			ls.head = ls.tail = NULL;
		else {
			ls.head = ls.head->next;
			p->next = NULL;
			ls.head->prev = NULL;
		}
		delete p;
		p = NULL;
	}
}
void readFile(DoublyLinkedList& ls) {
	ifstream myFile("data_sv.txt");
	if (myFile.is_open()) {
		while (!myFile.eof()) {
			SinhVien sv;
			myFile >> sv.mssv;
			myFile.ignore();
			getline(myFile, sv.hoTen);
			myFile.getline(sv.maLop, 9, '\n');
			getline(myFile, sv.queQuan);
			myFile.getline(sv.ngaySinh, 11, '\n');
			myFile >> sv.phoneNumber;
			for (int i = 0; i < DIEMTB; i++) {
				myFile >> sv.diemTB[i];
			}
			addNodeOrderList(ls, sv);
		}
		myFile.close();
	}
}
NodeSinhVien* search(DoublyLinkedList ls, string key) {
	NodeSinhVien* p = ls.head;
	while (p != NULL) {
		if (p->sv.hoTen == key || p->sv.maLop == key)
			return p;
		p = p->next;
	}
	return p;
}
void display(DoublyLinkedList ls) {
	if (ls.head != NULL) {
		NodeSinhVien* p = ls.head;
		while (p != NULL) {
			xuatTT1SV(p->sv);
			/*int opt;
			cout << "1:Tiep/0:Tro lai:=> ";
			cin >> opt;
			do
			switch (opt)
			{
			case 0:
				p = p->prev;
				break;
			case 1:
				p = p->next;
				break;
			default:
				cout << "ERROR!!!\n";
				break;
			}
			while (opt != 1 && opt != 0);
			system("cls");*/
			p = p->next;
		}
	}
}
void delAll(DoublyLinkedList& ls) {
	if (ls.head != NULL) {
		while (ls.head != NULL) {
			delFirst(ls);
		}
	}
}
void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}
void displayShortcut(DoublyLinkedList ls, string key) {
	vector<int> res;
	int num = stoi(key);
	for (; num != 0;) {
		int du = num % 10;
		res.push_back(du);
		num /= 10;
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			if (res[i] < res[j])
				swap(res[i], res[j]);
		}
	}
	NodeSinhVien* p = ls.head;
	while (p != NULL) {
		cout << "===========THONG TIN SINH VIEN===========\n";
		for (int i = 0; i < res.size(); i++) {
			switch (res[i])
			{
			case 1:
				cout << "MSSV: " << p->sv.mssv << endl;
				break;
			case 2:
				cout << "Ho va ten: " << p->sv.hoTen << endl;
				break;
			case 3:
				cout << "Ma lop: " << p->sv.maLop << endl;
				break;
			case 4:
				cout << "Que quan: " << p->sv.queQuan << endl;
				break;
			case 5:
				cout << "Ngay sinh: " << p->sv.ngaySinh << endl;
				break;
			case 6:
				cout << "So dien thoai: " << p->sv.phoneNumber << endl;
				break;
			case 7:
				cout << "Diem trung binh 3 mon: ";
				for (int i = 0; i < DIEMTB; i++) {
					cout << p->sv.diemTB[i] << " ";
				}
				break;
			default:
				break;
			}
		}
		cout << "\n========================================\n\n";
		p = p->next;
	}
}

int main() {
	DoublyLinkedList ls;
	init(ls);
	readFile(ls);
	cout << "======DANH SACH THONG TIN SINH VIEN====\n";
	cout << "1: mssv\n";
	cout << "2: Ho va ten\n";
	cout << "3: Ma lop\n";
	cout << "4: Que quan\n";
	cout << "5: Ngay sinh\n";
	cout << "6: So dien thoai\n";
	cout << "7: diem TB 3 mon\n";
	cout << "Nhap lua chon(vd: 123 or 1423): \n";
	displayShortcut(ls, "5672");
	

	delAll(ls);
	cout << "===================CLEAR================\n";

	return 1;
}