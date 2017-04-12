//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Project7.cpp          ASSIGNMENT #:  6            Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Micaiah Skolnick                                              *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                            DUE DATE:  April 14, 2017                    *
//*                                                                                                   *
//*****************************************************************************************************
//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: ******************************************************NEED TO DO THIS*************************
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : 

//  //*   PROCESS: ******************************************************NEED TO DO THIS*************************

//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
#include "TreeClass.h"
using namespace std;
int lineCount;
int MAXLINECOUNT;
//*****************************************************************************************************
void newPage(ofstream&dataOUT) {
	// Receives – the output file
	// Task - Insert blank lines to fill the rest of the current page
	// Returns - Nothing
	while (lineCount < MAXLINECOUNT) {
		dataOUT << endl;
		lineCount++;
	}
	lineCount = 0; // Reset the line count to 0 for next page.
}
//*****************************************************************************************************
//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile)
{       // Receives – the output file
		// Task - Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Micaiah Skolnick ";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(27) << "Spring 2017";
	Outfile << setw(30) << "Assignment #6" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- - " << endl << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION HEADER  ***************************************
//*************************************  FUNCTION FOOTER  *********************************************
void Footer(ofstream &Outfile)
{
		// Receives – the output file
		// Task - Prints the output salutation
		// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION FOOTER  ***************************************
void processData(ifstream&dataIN) {
	// Receives – The input file
	// Task - Process data from the input file
	// Returns - A binary tree filled with data from the input file

	char code;

	dataIN >> ws >> code; //Seed read first command code
	

	while (code == 'I' || code == 'D') {
		NodeType newNode;
		if (code == 'I') { //If the code is 'I' Insert a node
				//Read in each of the elements of the new node
			dataIN >> newNode.ID >> newNode.Name >> newNode.QOnHand >> newNode.QOnOrder;
				//Insert the node into the tree
			iTree.insert(newNode);

		}


		dataIN >> ws >> code;  //Read in the next code

	}


}
//*****************************************************************************************************
int main() {
	// Receives – Nothing
	// Task - Call each necessary function of the program in order
	// Returns - Nothing
	// Declare variables used in program.	 
	ifstream dataIN("SampleInput.txt"); // Open the file containing data.
	ofstream dataOUT("dataOUT.doc"); // Create and open the file to write data to.	
	
	lineCount = 0;
	MAXLINECOUNT = 54;
	 	
	Header(dataOUT); // Print data header.
	processData(dataIN); // Process the data in the input file
	
	newPage(dataOUT); // Insert a page break before the footer
	Footer(dataOUT); // Print footer. 
	dataIN.close(); // Close input data file. 
	dataOUT.close(); // Close output data file.

	return 0;
}