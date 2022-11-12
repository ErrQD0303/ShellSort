#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>

void inputArray(int* a, int& count) {
	std::string str;
	char* str1 = new char[500];
	std::cout << "Please input the array you want to sort:" << std::endl;
	getline(std::cin, str);
	char* ch;
	str.copy(str1, 100);
	ch = strtok(str1, " .");
	while (1) {
		a[count] = atoi(ch);
		ch = strtok(NULL, " .");
		if (ch == NULL || (ch[0] < 48 && ch[0] != 45) || ch[0] > 57) {
			count++;
			break;
		}
		count++;
	}
	delete[] str1;
	str1 = nullptr;
}

void printSortedArray(int* a, int count) {
	std::cout << "The Array after has been sorted is:\n";
	for (int j = 0; j < count; j++)
		std::cout << a[j] << " ";
}

void insertionSort(int** a, int count) {
	if (count > 1) {
		insertionSort(a, count - 1);
		int pos = count - 2;
		for (pos; *a[count - 1] < *a[pos] && pos > 0; pos--);
		if (*a[count - 1] < *a[pos])
			pos--;
		if (pos != count - 1) {
			int temp = *a[count - 1];
			int i = count - 1;
			while (i > pos + 1) {
				*a[i] = *a[i - 1];
				i--;
			}
			*a[i] = temp;
		}
	}
}

void shellSort(int* a, int count, int gap) {
	if (gap > 0) {
		int** b = new int* [100];
		for (int i = 0; i < gap; i++) {
			int dem = 0;
			int j = 0;
			for (j = 0; i + j * gap < count; ++j) {
				b[dem] = &a[i + j * gap];
				dem++;
			}
			insertionSort(b, dem);
		}
		shellSort(a, count, gap / 2);
		delete[] b;
		b = nullptr;
	}
}

int main() {
	int* a = new int[150];
	int count = 0;
	inputArray(a, count);
	auto start = std::chrono::high_resolution_clock::now();
	shellSort(a, count, count / 2);
	printSortedArray(a, count);
	delete[] a;
	a = nullptr;
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "\nExecute time:" << duration.count() << " microseconds" << std::endl;
	return 0;
}