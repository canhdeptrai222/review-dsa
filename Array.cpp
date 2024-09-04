#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#define MAX 100
using namespace std;

void inputArray(int a[], int& n) {
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 100 + 1;
	}
}
void outputArray(int a[], const int n) {
	cout << "Cac phan tu cua mang: ";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int search(int a[], int n, int x) {
	for (int i = 0; i < n; i++) {
		if (x == a[i])
			return i;
	}
	return -1;
}
void addNum(int a[], int& n, int x) {
	if (n == MAX)
		return;
	if (n == 0)
		a[0] = x;
	else {
		a[n] = x;
	}
	n++;
}
void delLastElement(int a[], int& n) {
	a[n - 1] = -1;
	n--;
}
void delElement(int a[], int& n, int index) {
	for (int i = index; i < n; i++) {
		a[i] = a[i + 1];
	}
	n--;
}
void addElementByIndex(int a[], int& n, int index, int x) {
	for (int i = n - 1; i >= index; i--) {
		a[i + 1] = a[i];
	}
	a[index] = x;
	n++;
}
int findMax(int a[], int n) {
	int max = a[0];
	for (int i = 1; i < n; i++) {
		if (max < a[i])
			max = a[i];
	}
	return max;
}
int findSecondMax(int a[], int n) {
	int FirstMax = a[0];
	int SecondMax = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > FirstMax) {
			SecondMax = FirstMax;
			FirstMax = a[i];
		}
		else if (a[i] > SecondMax)
			SecondMax = a[i];
	}
	return SecondMax;
}
void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}
void selectionSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int index = i;
		for (int j = i + 1; j < n; j++) {
			if (a[index] < a[j])
				index = j;
		}
		swap(a[i], a[index]);
	}
}
void insertionSort(int a[], int n) {
	for (int i = 1; i < n - 1; i++) {
		int x = a[i];
		int j = i - 1;
		while (j >= 0 && x >= a[j]) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = x;
	}
}

void bubbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] < a[j + 1])
				swap(a[j], a[j + 1]);
		}
	}
}

void interchangeSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[i] < a[j])
				swap(a[i], a[j]);
		}
	}
}

void quickSortWithRecursion(int a[], int left, int right) {
	int pivot = (left + right) / 2;
	int l = left;
	int r = right;
	while (l <= r) {
		while (a[l] > a[pivot])
			l++;
		while (a[r] < a[pivot])
			r--;
		if (l <= r) {
			swap(a[l], a[r]);
			l++;
			r--;
		}
		if (left < r)
			quickSortWithRecursion(a, left, r);
		if (right > l)
			quickSortWithRecursion(a, l, right);
	}
}

int binarySearch(int a[], int n, int x) {
	int left = 0; int right = n - 1;
	int mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (a[mid] == x)
			return mid;
		else if (x > a[mid])
			right = mid - 1;
		else if (x < a[mid])
			left = mid + 1;
	}
	return -1;
}



int main()
{


	return 0;
}