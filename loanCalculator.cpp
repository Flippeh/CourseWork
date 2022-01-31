// David B
// 
// loanCalculator.cpp
// Using -std=c++11
// Learned to add cin.clear() to avoid certain issues from a classmate named Jack.
// Used a Stackoverflow question regarding verifying input data is correct datatype and to learn about setw()
//
// For the most part, I did this project entirely on my own and struggled with the table, but figured 
// it out through trial and error. This took me many many hours.


#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

int main() {



	double loan, intRate, monthlyPay;

	//sets the formatting for the output numbers
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);


	cout << "Loan Amount: ";
	cin >> loan;

	// checks for positive loan amount
	// this caused me a big headache, but I believe adding the "|| !loan" will check if numerical input or not

	while (loan <= 0 || !loan) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // prevents infinite loop if invalid input, ignores non-numerical inputs, found in Stackoverflow thread
		cout << "(Invalid loan): ";
		cin >> loan;
	}


	cout << "Interest Rate (% per year): ";
	cin >> intRate;
	
	// checks for positive & numeric interest rate
	while (intRate < 0 || !intRate) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "(Invalid interest rate): ";
		cin >> intRate;
	}
	
	//converts the interest rate to a monthly one
	intRate /= 12;
	double intRateP = intRate / 100; //interest rate into a percent

	cout << "Monthly Payments: ";
	cin >> monthlyPay;

	// checks for positive & numeric monthly payment amount
	while (monthlyPay <= 0 || !monthlyPay) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "(Invalid payment): ";
		cin >> monthlyPay;
		
	}


	// checks to make sure monthly payment is enough to cover interest rate
	while ((loan * intRateP + loan) - monthlyPay >= loan) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "(Insufficient payment): ";
		cin >> monthlyPay;
	}

	// table header
	cout << endl;

	cout << "*****************************************************************\n"
		<< "\tAmortization Table\n" << "*****************************************************************\n"
		<< "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";

	

	// interest rate total and current month counter
	double intTotal = 0;
	int currentMonth = 0;

	// loop that fills the table
	while (loan > 0) {

		if (currentMonth == 0) {
			cout << currentMonth++ << "\t$" << loan;
			if (loan < 1000) cout << "\t";
					cout << "\tN/A\tN/A\tN/A\t\tN/A"; // thank you for including this
			}

			

				// loop that runs while the payments would not exceed past 0
				while (loan * (1 + intRateP) >= monthlyPay) {
					double oldLoan = loan; // THIS RIGHT HERE took me 2 hours of sitting and constantly changing things to figure out					
					loan = loan * (1 + intRateP) - monthlyPay;

					//using setw() to align my columns,, this was a lot of trial and error 
					cout << "\n" << left << setw(8) << currentMonth;
					cout << "$" << setw(15) << loan 
						 << "$" << setw(7)  << monthlyPay
					 	 << setw(8) << intRate 
						 << "$" << setw(15) << oldLoan * intRateP
					  	 << "$" << setw(11) << monthlyPay - intRateP * oldLoan;

					intTotal += oldLoan * intRateP;
					currentMonth++;
				}

			
				// if statement for the final payment
				if (loan * (1 + intRateP) < monthlyPay && loan != 0) { // added "&& loan != 0" to avoid an error I had with test case 4
					double oldLoan = loan;

					monthlyPay = loan * (1 + intRateP);
					cout << "\n" << currentMonth;
					cout << "\t$0.00" 
						 << "\t\t$" << monthlyPay 
						 << "\t" << intRate << "\t$" 
						 << oldLoan * intRateP
						 << "\t\t$" << monthlyPay - intRateP * oldLoan;
					
					intTotal += oldLoan * intRateP;
				    currentMonth++;

				}
				
	
			cout << endl;

			cout << "****************************************************************\n";
			cout << "\nIt takes " << --currentMonth << " months to pay off "
				<< "the loan.\n"
				<< "Total interest paid is: $" << intTotal;
			cout << endl << endl;
			return 0;
		}
	}


