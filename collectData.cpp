// David Braswell for COMP 3270 Intro to Algorithms
// Compiled with g++ collectData.cpp -std=c++11 and run with ./a.out
// C++ Program to calculate the execution time of the ComputeSumPowers() algorithm

#include <iostream>
#include <chrono>
#include <fstream>
#include <math.h>
using namespace std::chrono;

double ComputeSumPowers(double x, int n);
void function1(int n);
int function2(int n);
int function3(int n);

int main() {
	int limit = 100000;
	double x = .25;
	
	

	// create the output files
	std::ofstream output;
	std::ofstream funct1;
	std::ofstream funct2;
	std::ofstream funct3;
	output.open("output.csv"); // normal T(n) = n^2 output
	funct1.open("T(n)dividesqrt(n).csv");
	funct2.open("T(n)dividepow(n,2).csv");
	funct3.open("T(n)divide(nlog(n)).csv");


	for (int i = 100; i < limit + 1; i+=100) {
		//times the execution time
		auto start = high_resolution_clock::now();
		ComputeSumPowers(.25, i);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);

		// the calculations of T(n)/sqrt(n), T(n)/n2, and T(n)/n*ln(n) 
		double fun1 = duration.count() / sqrt(i);
		double fun2 = duration.count() / pow(i, 2);
		double fun3 = duration.count() / (i * log(i));

		// printing the values to their respective files
		output << i << "," << duration.count() << "\n"; // normal T(n) = n^2
		funct1 << i << "," << fun1 << "\n";
		funct2 << i << "," << fun2 << "\n";
		funct3 << i << "," << fun3 << "\n";
	}

	output.close();
	funct1.close();
	funct2.close();
	funct3.close();
	
}
// algorithm we are required to implement
double ComputeSumPowers(double x, int n) {
	double sum = 0;
	
	for (int i = 1; i < n; i++) {
		double prod = 1;
		for (int j = 1; j < i; j++) {
			prod = prod * x;
		}
		sum = sum + prod;
	}
	return sum;
}

// This was an early implementation that I ended up not using -David
// 
//void function1(int n) {
//	std::ofstream fun1;
//	fun1.open("function1.csv");
//	for (int i = 1; i < n + 1; i++) {
//		double calc = i / sqrt(i);
//		fun1 << i << "," << calc << "\n";
//	}
//
//	
//}
