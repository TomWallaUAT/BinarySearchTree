// BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Includes for code
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>

//Namespaces being used
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

//ClassDefinition  (Generic)
template <class T>
class Node {
public:
	Node* prev;
	T data;
	Node* next;
};

template <class T>
class DblLinkedList {
private:
	int length;
	Node<T>* head;

public:
	int getLength() { return length; }
	DblLinkedList() {
		length = 0;
		head = NULL;
	}

	void display() {
		Node<T>* curr = this->head;
		int i = 1;

		//Get the Head and walk thru it from the beginning to end dumping the results
		while (curr) {
			cout << "Node " << i << ": [" << curr->data << "]" << endl;
			curr = curr->next;
			i++;
		}
	}

	void displayWithRoute() {
		Node<T>* curr = this->head;
		int i = 1;

		//Get the Head and walk thru it from the beginning to end dumping the detailed results
		while (curr) {
			if (curr->prev == NULL) {
				cout << "Node " << i << ": Prev [NULL]";
			}
			else {
				cout << "Node " << i << ": Prev [" << curr->prev->data << "]";
			}

			cout << "  - Curr [" << curr->data << "]";

			if (curr->next == NULL) {
				cout << " - Next [NULL]" << endl;
			}
			else {
				cout << " - Next [" << curr->next->data << "]" << endl;
			}

			curr = curr->next;
			i++;
		}
	}

	void insertBegin(T ItemData) {
		Node<T>* tmp = new Node<T>();

		//creat node and assign data
		tmp->data = ItemData;
		tmp->prev = NULL;


		if (this->length == 0) {
			//if the DblLL is empty make this the first node
			tmp->next = NULL;
		}
		else {
			//if not, put node in the first position
			tmp->next = head;
			head->prev = tmp;
		}
		//Newly inserted node is now Head
		head = tmp;

		//add 1 to the number of items
		length++;
	}

	void insertEnd(T ItemData) {
		Node<T>* tmp = new Node<T>();
		Node<T>* node = new Node<T>();

		//creat node and assign data
		tmp->data = ItemData;

		if (this->length == 0) {
			//if the DblLL is empty make this the first node
			tmp->prev = NULL;
			tmp->next = NULL;
			head = tmp;
		}
		else {
			//if not, put node in the last position
			tmp->next = NULL;
			node = head;
			while (node->next != NULL) {
				//move to last node position
				node = node->next;
			}
			node->next = tmp;
			tmp->prev = node;
		}
		//add 1 to the number of items
		length++;
	}

	void removeItem(T ItemData) {
		Node<T>* node = new Node<T>();

		//Let Find do the work for me
		node = findItem(ItemData);

		//If the node is found (then delete it)
		if (node != NULL) {
			//first re-assign the pointers to Prev and Next nodes
			node->next->prev = node->prev;
			node->prev->next = node->next;
			//decrease the count by 1
			length--;
		}
		//Deallocate memory
		node = NULL;
	}

	Node<T> * findItem(T ItemData) {
		Node<T>* curr = this->head;
		bool bFound = false;

		//Loop until i find the node that matches the data
		while (curr && !bFound) {
			if (curr->data == ItemData) {
				//Found it
				bFound = true;
			}
			if (!bFound) { curr = curr->next; }  //Didn't find it, keep lookign
		}
		if (!bFound) { curr = NULL; }
		return curr;  //Heres what i found (Null or Node)
	}

};


//Methods for Main Application
void Demo2(int iIterations, bool ShowDetails) {
	DblLinkedList<int> dll;

	//Generates a DblLinkedList of Random number from 0 to 1000
	//The number of items depends on the iIterations it is told to run
	for (int i = 0; i < iIterations; ++i) {
		dll.insertEnd(rand() % 1000);
	}
	(ShowDetails) ? dll.displayWithRoute() : dll.display();
	cout << "-------------------------------------------------------" << endl;
	cout << "Items: " << dll.getLength() << endl;
}

void Demo1(bool ShowDetails) {
	DblLinkedList<string> dll;
	Node<string>* myNode = new Node<string>();
	string searchString = "";

	//Negative Test (Find item in empty List and remove Item in Empty List)
	cout << "Items: " << dll.getLength() << endl;
	myNode = dll.findItem("There");
	cout << "(Negative Test on Empty List) - " << "dll.findItem(\"There\")\; - " << "return: [" << ((myNode == NULL) ? "NULL" : myNode->data) << "]" << endl;
	dll.removeItem("There");
	cout << "(Negative Test on Empty List) - " << "dll.removeItem(\"There\")\; - " << "No Return or Failure" << endl;
	cout << "-------------------------------------------------------" << endl;

	//CREATES NODE
	cout << "(Create List of 3 Items)" << endl;
	dll.insertEnd("Tom");
	dll.insertEnd("Wallace");
	dll.insertEnd("MS549");
	(ShowDetails) ? dll.displayWithRoute() : dll.display();
	cout << "Items: " << dll.getLength() << endl;
	cout << "-------------------------------------------------------" << endl;

	cout << "(Insert \"There\" in list at the beginning)" << endl;
	dll.insertBegin("There");
	(ShowDetails) ? dll.displayWithRoute() : dll.display();
	cout << "Items: " << dll.getLength() << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "(Insert \"Hello\" in list at the beginning)" << endl;
	dll.insertBegin("Hello");
	(ShowDetails) ? dll.displayWithRoute() : dll.display();
	cout << "Items: " << dll.getLength() << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "(Search for \"Lilly\")" << endl;
	searchString = "Lilly";
	myNode = dll.findItem(searchString);
	if (myNode != NULL) {
		cout << "Found Value: " << myNode->data << endl;
	}
	else {
		cout << "Item \"" << searchString << "\" Not Found" << endl;
	}
	cout << endl << "(Search for \"Tom\")" << endl;
	searchString = "Tom";
	myNode = dll.findItem(searchString);
	if (myNode != NULL) {
		cout << "Found Value: " << myNode->data << endl;
	}
	else {
		cout << "Item \"" << searchString << "\" Not Found" << endl;
	}

	cout << "-------------------------------------------------------" << endl;
	cout << "(Remove Item \"There\")" << endl;
	dll.removeItem("There");
	(ShowDetails) ? dll.displayWithRoute() : dll.display();
	cout << "Items: " << dll.getLength() << endl;

}

void DisplayMenu() {
	system("cls");
	cout << "Note: Detailed Display (DtlDisp) shows Previous, Current and Next Node information" << endl;
	cout << "      Simple Display (SmpDisp) shows just the values of an node" << endl;
	cout << "      Timer (Time) shows before and after time" << endl << endl;
	cout << "0  - Exit Application" << endl;
	cout << "1  - See Demo of using Node<string>. Let me see it run edition (SmpDisp)" << endl;
	cout << "2  - See Demo of using Node<string>. Let me see it run edition (DtlDisp)" << endl;
	cout << "3 -  See Demo of using Node<int>. Let me see it run edition 1000 (SmpDisp)" << endl;
	cout << "4  - See Demo of using Node<int> 10 runs (Time & SmpDisp)" << endl;
	cout << "5  - See Demo of using Node<int> 100 runs (Time & SmpDisp)" << endl;
	cout << "6  - See Demo of using Node<int> 1,000 runs (Time & SmpDisp)" << endl;
	cout << "7  - See Demo of using Node<int> 10,000 runs (Time & SmpDisp)" << endl;
	cout << "8  - See Demo of using Node<int> 10 runs (Time & DtlDisp)" << endl;
	cout << "9  - See Demo of using Node<int> 100 runs (Time & DtlDisp)" << endl;
	cout << "10 - See Demo of using Node<int> 1,000 runs (Time & DtlDisp)" << endl;
	cout << "11 - See Demo of using Node<int> 10,000 runs (Time & DtlDisp)" << endl;

	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "Your Selection ?: ";
}

int GetInput() {
	int iInput;
	cin >> iInput;
	return iInput;
}



void MenuLogic(int iMenuItem) {
	bool bShowTimer = false;  // Boolean for Showing timer or not
	auto StartTime = high_resolution_clock::now(); //Clock Timer Start (Initializing)

	//Case Statement for DisplayMenu - Logic behind the selections
	switch (iMenuItem) {
	case 0:
		//Say Bye and pause for 2 seconds then continue
		cout << endl << endl << "See ya Later!" << endl;
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(2));
		exit(0);  //exit the appliction;
		break;
	case 1:
		Demo1(false);  //Shows Demo of Node<T> as string  (shows just node values)
		break;
	case 2:
		Demo1(true);  //Shows Demo of Node<T> as string  (shows prev,data,next info)
		break;
	case 3:
		Demo2(1000, false); //Shows demo of Node<T> as int (Generates Random Number for 1000 runs) Let me see it run edition
		break;
	case 4:
		Demo2(10, false); //Shows demo of Node<T> as int (Generates Random Number for 10 runs)
		bShowTimer = true;
		break;
	case 5:
		Demo2(100, false); //Shows demo of Node<T> as int (Generates Random Number for 100 runs)
		bShowTimer = true;
		break;
	case 6:
		Demo2(1000, false); //Shows demo of Node<T> as int (Generates Random Number for 1,000 runs)
		bShowTimer = true;
		break;
	case 7:
		Demo2(10000, false); //Shows demo of Node<T> as int (Generates Random Number for 10,000 runs)
		bShowTimer = true;
		break;
	case 8:
		Demo2(10, true); //Shows demo of Node<T> as int (Generates Random Number for 10)
		bShowTimer = true;
		break;
	case 9:
		Demo2(100, true); //Shows demo of Node<T> as int (Generates Random Number for 100)
		bShowTimer = true;
		break;
	case 10:
		Demo2(1000, true); //Shows demo of Node<T> as int (Generates Random Number for 1,000)
		bShowTimer = true;
		break;
	case 11:
		Demo2(10000, true); //Shows demo of Node<T> as int (Generates Random Number for 10,000)
		bShowTimer = true;
		break;
	default:
		//What did they hit again? huh? (not in this list)
		cout << endl << "Invalid selection, please try again!" << endl;
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(1));
		break;
	}

	if (bShowTimer) {
		//show the timer if the menu item ask for it. (two options seconds or milliseconds - defaulted to milliseconds)
		auto StopTime = high_resolution_clock::now();
		auto TimeItTook = duration_cast<milliseconds>(StopTime - StartTime);
		cout << "Run Duration: " << TimeItTook.count() << " ms" << endl;
		//cout << "Run Duration: " << (double)TimeItTook.count()/1000 << " seconds" << endl;
	}
}

int main()
{
	int iInput = 0;
	char c;  //used for cin.peek() - so i can actively monitor the key the user is pressing - Looks for CR (10)

	do {
		//Loop to display menu until user exits (selects 0)
		DisplayMenu();
		iInput = GetInput();
		MenuLogic(iInput);
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << "Press enter to continue..." << endl;

		//Dont wait for enter if it is an invalid selection
		if (iInput >= 0 && iInput <= 11) {
			//Peek at what key the user has hit
			cin.get(c);
			c = cin.peek();
			if (c != 10) {
				//if not enter put it back in the CIN
				cin.putback(c);
			}
		}
	} while (iInput != 0);

	//See ya
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
