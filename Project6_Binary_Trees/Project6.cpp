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
#include "Variables.h"
using namespace std;
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
void printMessage(char opType, string IDtoPrint, bool opSuccess) {
		//Receives – The type of operation, ID to print, and whether operation was successful
		//Task - Print a message to the user indicating whether operation succeeded
		//Returns - Nothing
	if (opSuccess) { //Print the corresponding message if the operation was successful
		if (opType == 'I') {
			dataOUT << "Item ID Number " << IDtoPrint << " successfully entered into database.";
		}
		else if (opType == 'D') {
			dataOUT << "Item ID Number " << IDtoPrint << " successfully deleted from database.";
		}
		else if (opType == 'S' || opType == 'R'){
			dataOUT << "Quantity on Hand for item " << IDtoPrint << " successfully updated.";
		}
		else if (opType == 'O') {
			dataOUT << "Quantity on order for item " << IDtoPrint << " successfully updated.";
		}
		else {	return; }		
	}
	else { //Print the corresponding message if the operation failed
		if (opType == 'I') {
			dataOUT << "ERROR - Attempt to insert a duplicate item " << IDtoPrint << " into the database.";
		}
		else if (opType == 'D') {
			dataOUT << "ERROR - Attempt to delete an item " << IDtoPrint << " not in the database list.";
		}
		else if (opType == 'P') {
			dataOUT << "Item " << IDtoPrint << " not in database. Print failed.";
		}
		else {
			dataOUT << "Item " << IDtoPrint << " not in database. Data not updated.";
		}
	}
	//Add a line of dashes after printing output message
	dataOUT << endl << "--------------------------------------------------------------------" << endl; 	
	lineCount+=2; //Increment the line counter
}
//*****************************************************************************************************
void printHeaderForAll() {
		//Receives – Nothing
		//Task - Prints a header for when entire tree is printed
		//Returns - Nothing
	dataOUT << "	               JAKE’S HARDWARE INVENTORY REPORT" << endl;
	dataOUT << "	Item             Item                    Quantity       Quantity" << endl;
	dataOUT << "	ID Number        Description             On hand        On Order" << endl;
	dataOUT << "--------------------------------------------------------------------" << endl;
	lineCount += 4; // Increment line counter

}
//*****************************************************************************************************
void processData() {
		//Receives – The input file
		//Task - Process data from the input file
		//Returns - A binary tree filled with data from the input file
	char code,code2,newName[21];
	bool opSuccess = false;
	int newQuantity;
	string IDtoSearch;
	dataIN >> ws >> code; //Seed read first command code
	while (code != 'Q') {
		NodeType newNode;
		if (code == 'I') { //If the code is 'I' Insert a node
				
			dataIN >> IDtoSearch >> ws;
			newNode.ID = IDtoSearch; //Read in the ID of the new node
			dataIN.getline(newName, 20); // Read in the new name to a character array
			newNode.Name = newName; // Add char array to node as the name
			dataIN >> newNode.QOnHand >> newNode.QOnOrder; // Get the QOnHand and QOrdered
				//Insert the node into the tree if it is not already there
			if (!iTree.searchTree(IDtoSearch)) {
				opSuccess = iTree.insertNode(newNode);
			}
			else {
				opSuccess = false;
			}
			
		}
		else if (code == 'D') {
			dataIN >> IDtoSearch >> ws; //Read in the ID of the node to delete
			dataIN.getline(newName, 20); // Read in the new name to a character array
			
			opSuccess = iTree.deleteNode(IDtoSearch);//Delete the node matching this ID
		
		}
		else if (code == 'P') {
			dataIN >> code2;
			if (code2 == 'E') {
				newPage(dataOUT);//Space out to new page for entire printing of tree
				printHeaderForAll(); //Print a header for the tree printout
				opSuccess = iTree.printEntireTree(); //Print entire tree
				newPage(dataOUT);//Space out rest of page for more output
			}
			if (code2 == 'N') {
				dataIN >> IDtoSearch;
				if (iTree.searchTree(IDtoSearch)) {
					opSuccess = iTree.updateNode(IDtoSearch, code, 0);//Print an individual node
				}
				else {
					opSuccess = false;
				}
						
			}			
		}
		else {
			dataIN >> IDtoSearch >> newQuantity;
			if (iTree.searchTree(IDtoSearch)) {
				opSuccess = iTree.updateNode(IDtoSearch, code, newQuantity);//Update an individual node
			}
			else {
				opSuccess = false;
			}		
		}
		printMessage(code, IDtoSearch, opSuccess); //Print a message to alert user of outcome

		dataIN >> ws >> code;  //Read in the next code
	}


}
//*****************************************************************************************************
int main() {
	// Receives – Nothing
	// Task - Call each necessary function of the program in order
	// Returns - Nothing
	// Declare variables used in program.	 
	dataIN.open("SampleInput.txt"); // Open the file containing data.
	dataOUT.open("dataOUT.doc"); // Create and open the file to write data to.	
	
	lineCount = 0;
	MAXLINECOUNT = 20; //Should be 54
	 	
	Header(dataOUT); // Print data header.
	processData(); // Process the data in the input file
	
	newPage(dataOUT); // Insert a page break before the footer
	Footer(dataOUT); // Print footer. 
	dataIN.close(); // Close input data file. 
	dataOUT.close(); // Close output data file.

	return 0;
}