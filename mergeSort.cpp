// David Braswell and Emily Richardson for Intro to Algorithms
// compiled by writing "g++ mergeSort.cpp -std=c++11"


#include <iostream>
#include <fstream>
#include <tgmath.h>
#include <chrono>
#include <algorithm>

using namespace std::chrono;

int* mergeSort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);


int main() {
	//// initializing a test array to prove the implementation of merge sort works
	//int test[] = {3, 8, 24, 55, 17, 44, 100, 0, 1, 78};
	//mergeSort(test, 0, 9);
	//for (int i = 0; i < 10; i++) { /* print the sorted values */
	//	std::cout << test[i] << "\n";
	//}

	std::ofstream output;
	output.open("output.csv");
	output << "n,T(n)/n,T(n)/n*lg(n),T(n)/n*sqrt(n)" << "\n";
	int arraySize = 2000000;
	int* G = new int[arraySize];
	G[0] = 0; // ignore the 0th index

	srand(time(NULL)); // changes seed to generate a random set of numbers each time

	// generate an array G of size 2000000 populated with random amounts between 0 and 4,999,999
	for (int i = 1; i <= arraySize; i++) { 
		int randomNumber = rand() % 5000000;
		G[i] = randomNumber;		
	}

	int* A = new int[arraySize];

	for (int n = 1000; n <= arraySize; n += 1000) {
		std::copy_n(&G[0], n, &A[0]); // copies the first n elements of g into A
		auto start = high_resolution_clock::now();
		mergeSort(A, 0, n);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);

		if (n > 4000) { // ignore the first 4 results
			double function1 = duration.count() / n; // T(n) / n
			double function2 = duration.count() / n * log2(n); // T(n) / n*lg(n)
			double function3 = duration.count() / n * sqrt(n); // T(n) / n*sqrt(n)


			output << n << "," << function1 << "," << function2 << "," << function3 << "\n";
		}
	}
	output.close();
	
}


 int* mergeSort(int A[], int p, int r) {
	if (p < r) {
		int q = floor((p + r) / 2);
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
	return A;
}

void merge(int A[], int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;

	int L[n1 + 1];
	int R[n2 + 1];

	for (int i = 1; i <= n1; i++) {
		L[i] = A[p + i - 1];
	}
	for (int j = 1; j <= n2; j++) {
		R[j] = A[q + j];
	}
	L[n1 + 1] = 0x0fffffff;
	R[n2 + 1] = 0x0fffffff;

	int i = 1;
	int j = 1;

	for (int k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i = i + 1;
			}
		else {
			A[k] = R[j];
			j = j + 1;
		}
	}
}

