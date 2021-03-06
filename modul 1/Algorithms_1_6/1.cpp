/*
	Задача №1_6. 
	
	Дан массив целых чисел A[0..n). 
	Не используя других массивов переставить элементы массива A  в обратном порядке за O(n).
	n ≤ 10000.
*/
#include <iostream>
#include <assert.h>

void swap(int *a, int *b) {
	int c = *a;
	*a = *b;
	*b = c;
}

void reverse(int * const ptr, int& size) {
	for (int i = 0; i < size / 2; i++) 
		swap(&ptr[i], &ptr[size - i - 1]);
}

int main () {
	int masSize = 0;
	std::cin >> masSize;
	assert(masSize > 0);

	int *ptrMas = new int[masSize];
	
	for (int i = 0; i < masSize; i++) 
		std::cin >> ptrMas[i];
	
	reverse(ptrMas, masSize);
	for (int i = 0; i < masSize; i++)
		std::cout << ptrMas[i] << " ";
	std::cout << std::endl;
}

