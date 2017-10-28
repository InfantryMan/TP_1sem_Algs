/*
Задача 6_2. 
Широкая пирамида. 
Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.
N ≤ 300.
*/

#include <iostream>

long long min(long long a, long long b) {
	return a > b ? b : a;
}

long long calculate(int n, long long **pMas) {
	pMas[0][0] = 1;
	for (long long j = 1; j < n + 1; j++)
		pMas[j][0] = 0;
	for (long long j = 1; j < n + 1; j++)
		for (long long i = 1; i < j + 1; i++) {
			long long minIndex = min(i - 1, j - i);
			pMas[j][i] = pMas[j][i - 1] + pMas[j - i][minIndex];
		}
	return pMas[n][n];
}

int main() {
	int n = 0;
	std::cin >> n;
	long long **pMas = new long long*[n + 1];
	for (int i = 0; i < n + 1; i++)
		pMas[i] = new long long[n + 1];
	std::cout << calculate(n, pMas) << std::endl;
	for (int i = 0; i < n + 1; i++)
		delete[] pMas[i];
	delete[] pMas;
}