/*
3_1. 
		Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
		Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, 
	равного или превосходящего B[i]: A[k] >= B[i]. 
		Если такого элемента нет, выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)).
		n, m ≤ 10000.
*/

#include <iostream>
#include <assert.h>
#include <fstream>

int find (int *masA, int n, int elementFromB) { // binary search
	int first = 0;
	int last = 1;
	
	while ( (last < n) && (masA[last] < elementFromB) ) {
		first = last;
		last *= 2;
	}
	if (last > n)
		last = n;
	while ( first < last ) {
		int mid = ( first + last ) / 2;
		if ( masA[mid] < elementFromB)
			first = mid + 1;
		else
			last = mid;
	}
	if ( first == n ) 
		return n;
	else
		return first;
	
	
}

int main() {
	int n = 0 , m = 0;
	std::cin >> n >> m;
	assert(n > 0);
	assert(m > 0);
	int *a = new int [n];
	int *b = new int [m];
	for (int i = 0; i < n; i++) 
		std::cin >> a[i];
	for (int i = 0; i < m; i++)
		std::cin >> b[i];
	for (int i = 0; i < m; i++) 
		std::cout << find(a, n, b[i]) << " ";
	std::cout << std::endl;
	delete[] a;
	delete[] b;
}
		