#include <iostream>

int partition(int* arr, int l, int r) {
	int pivot = arr[l];
	int i = l + 1;
	int j = r;
	while (true) {
		while (i <= r && arr[i] < pivot)
			i++;
		while (arr[j]> pivot)
			j--;
		if (i >= j) {
			std::swap(arr[l], arr[j]);
			return j;
		}
		std::swap(arr[i], arr[j]);
		i++;
		j--;
	}
}

int findKStatistics(int* arr, int l, int r, int k) { //вызывает партишн и проверяет к
	int pivotPos = partition(arr, l, r);
	if (pivotPos == k) {
		return arr[pivotPos];
	}
	if (pivotPos < k) {
		return findKStatistics(arr, l, pivotPos + 1, r);
	}
	return findKStatistics(arr, l, pivotPos - 1, k);
}

int main() {
	int n = 0;
	int k = 0;
	std::cin >> n >> k;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}
	std::cout << findKStatistics(arr, 0, n - 1, k);
	return 0;
}