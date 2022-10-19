//Corner Grocer Project 3
//Steven Anderson

#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip> // used for the setw commands when building the histogram

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void PythonPrintOrWrite(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int OneItemRead(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

//prints the histogram of the data found in file frequency.dat
void Histogram() {
	//variables
	int count;
	string item, fileLine;

	//opening frequency.dat file that python should have written in
	ifstream file("frequency.dat");
	//while loop that reads each line of the file until no more lines exists,
	//then prints the item and * amount
	cout << left << setw(20) << "Item" << left << setw(15) << "Amount" << endl;
	cout << "--------------------------------------" << endl;
	while (getline(file, fileLine)) {
		istringstream iss(fileLine);// istringstream used to stream the fileline into a string
		if (!(iss >> item >> count)) { //breaks if there isnt both an item and count
			break; 
		}
		//prints the name of the item and a string consisting of *'s equal to the count
		cout << left << setw(20) << item << left << setw(15) << string(count, '*') << endl;
	}
	cout << "--------------------------------------" << endl;
	cout << endl << endl;
	//closing file for memory safety
	file.close();
}

//function to print the user menu
void Menu() {
	cout << "************************************" << endl;
	cout << "++++++What do you want to do?+++++++" << endl;
	cout << "++++(1) Frequency of all items++++++" << endl;
	cout << "++(2) Frequency of specific item++++" << endl;
	cout << "+++++++(3) Display Histogram++++++++" << endl;
	cout << "++++++++++++++(4) Exit++++++++++++++" << endl;
	cout << "************************************" << endl << endl;
}

//The CornerGrocer function used to call all functions needed except itself, keeps main stripped down
void CornerGrocer() {
	int userChoice = 0;

	//Intro message
	cout << "--------------Corner Grocer Inventory Tracker--------------" << endl << endl;
	while (userChoice != 4) { // Runs until user inputs 4 to quit
		//Menu for user inputs
		Menu();

		//user Input
		cin >> userChoice;
		while (userChoice > 4 || userChoice < 1) {//While loop to verify the user input is valid between 1-4
			//Error message
			cout << endl << ">>>>>Invalid input<<<<<" << endl << endl;
			//menu
			Menu();
			//user Input
			cin >> userChoice;
		}
		//if for userChoice 1 
		if (userChoice == 1) {
			cout << endl;
			//call function PythonPrintOrWrite to print the frequency of the data
			PythonPrintOrWrite("PrintFrequency");
			cout << endl << endl;
		}
		//if for userChoice 2
		if (userChoice == 2) {
			//variable
			string word;
			cout << "What item do you want the frequency of?" << endl;
			//user input for the item they wish to know the frequency of
			cin >> word;
			cout << endl;
			//printing the word and then calling the function OneItemRead the print the frequency of the user input 'word'
			cout << word << "   " << OneItemRead("PrintOneItemFrequency", word) << endl << endl;
		}
		//if for userChoice 3
		if (userChoice == 3) {
			cout << endl;
			//first call the function PythonPrintOrWrite to call python to fill the file frequency.dat with information from List.txt
			PythonPrintOrWrite("WriteToFileFrequency");
			//call function Histogram to print the data is historgram format
			Histogram();
		}
		if (userChoice == 4) {
			//exit message
			cout << "----------Exiting Corner Grocer Inventory Tracker----------" << endl;
			//exit userMenu
			exit;
		}	
	}
}

//main used just to run the CornerGrocer function
int main() {
	CornerGrocer();
}