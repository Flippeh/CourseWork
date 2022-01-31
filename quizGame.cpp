// David B
// 
// quizGame.cpp
// Using -std=c++11
// 
// used the project4 help file
// used https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/ for help understanding nodes

#include <iostream>
#include<string>
using namespace std;

// node structure
struct trivia_node {
		string question;
		string answer;
		int point;
		trivia_node* next;
};

// pointer
typedef trivia_node* ptr_node;

//globals for handling keeping track of # of questions asked and total points
int num_of_questions = 0;
int total_points = 0;

//prototypes
void init_question_list(ptr_node& q_list);
void add_question(ptr_node& q_list);
int ask_question(ptr_node, int);
void Unit_Test();

// creates two versions
//#define UNIT_TESTING
#define trivia_quiz

int main() {
	string cont;
	ptr_node node_list = new trivia_node;
	// changes based on #define
#ifdef trivia_quiz
	cout << "*** Welcome to David's trivia quiz game ***\n";

	init_question_list(node_list);
	add_question(node_list);

	// ask user if they want another question added
	cout << "Continue? (Case Sensitive) (Yes/No): ";
	cin.clear();
	getline(cin, cont);
	if (cont.compare("Yes") == 0) {
		add_question(node_list);
	}
	
	ask_question(node_list, num_of_questions);

	cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
	return 0;
}
#endif
//For unit test
#ifdef UNIT_TESTING

cout << "***This is a debugging version***\n";
Unit_Test();
return 0;
}
#endif

// Initiates the question list node
void init_question_list(ptr_node& q_list) {
	string t;
	ptr_node n2;
	ptr_node n3;
	ptr_node n1;
	n1 = q_list;
	n2 = new trivia_node();
	n3 = new trivia_node();
	// 3 presets node
	n1->question = "How long was the shortest war on record? (Hint: how many minutes)";
	num_of_questions++;
	n1->answer = "38";
	n1->point = 100;
	n1->next = n2;
	n2->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
	num_of_questions++;
	n2->answer = "Bank of Italy";
	n2->point = 50;
	n2->next = n3;
	n3->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
	num_of_questions++;
	n3->answer = "Wii Sports";
	n3->point = 20;
	n3->next = NULL;
}
// function to add questions to linked list
void add_question(ptr_node& q_list) {
	string cont;
	
	ptr_node new_node = new trivia_node;
		cout << "Enter a question: ";
		cin.clear();
		getline(cin, new_node->question);
		cout << "Enter an answer: ";
		cin.clear();
		getline(cin, new_node->answer);
		cout << "Enter award points: ";
		cin >> new_node->point;
		cin.ignore();
		
		new_node->next = q_list;
		
		//increments number of questions
		num_of_questions++;
	
		q_list = new_node;
	
}

// function for asking questions
int ask_question(ptr_node q_list, int num_ask) {
	ptr_node current_ptr = q_list;
	total_points = 0;
	string answer;
	if (q_list == NULL) {  // checks to see if q_list is NULL
		return 0;
	}
	if (num_ask < 1) {
		cout << "Warning - the number of trivia to be asked must equal"
			<< " or be larger than 1.";
	}
	else if (num_of_questions < num_ask) {
		cout << "Warning - There is only " << num_of_questions << " trivia in the list.";
	}
	else {
		for (int x = 0; x < num_ask; x++) {    // loop for asking multiple questions
			cout << "\nQuestion: " << current_ptr->question << endl;
			cout << "Answer: ";
			cin.clear();
			getline(cin, answer);
			if (answer.compare(current_ptr->answer) == 0) { // true result
				total_points += current_ptr->point;
				cout << "Your answer is correct. You receive " << current_ptr->point << " points."
					<< "\nYour total points: "
					<< total_points;

			}
			else {
				cout << "Your answer is wrong. The correct answer is: "
					<< current_ptr->answer;
				cout << "\nYour total points: "
					<< total_points;
			}
			cout << "\n";
			
			current_ptr = current_ptr->next;
		}
	}
	return 0;
}

// unit test
void Unit_Test() {
	ptr_node node_list = new trivia_node;
	init_question_list(node_list);
	cout << "Unit Test Case 1: Ask no question. The program should ive a warning message." << endl;
	ask_question(node_list, 0);
	cout << "\nCase 1 Passed\n\n";

	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.";
	ask_question(node_list, 1);
	cout << "\nCase 2.1 passed\n\n";

	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.";
	ask_question(node_list, 1);
	cout << "\nCase 2.2 passed\n\n";

	cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list.";
	ask_question(node_list, 3);
	cout << "\nCase 3 passed\n\n";

	cout << "Unit Test Case 4: Ask 5 questions in the linked list.\n";
	ask_question(node_list, 5);
	cout << "\nCase 4 passed\n\n";

	cout << "\n*** End of the Debugging Version ***";
}	