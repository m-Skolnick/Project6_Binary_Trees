//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  TreeClass.cpp                  ASSIGNMENT #: 6                              *
//*                                                                                                   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     :  *************NEED TO DO THIS***********************                    *
//*                                                                                                   *
//*****************************************************************************************************
#ifndef TREECLASS_H
#define TREECLASS_H
#include "Variables.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//*****************************************************************************************************
struct NodeType {
		// The structure "NodeType" holds each inventory file.
	int QOnHand, QOnOrder;
	string ID,Name;
	NodeType *Lptr,*Rptr,*parent;
};
//*****************************************************************************************************
class BinaryTreeClass {
public:
	BinaryTreeClass();
	bool insertNode(NodeType);
	bool printEntireTree();
	void printEachNode(NodeType*);
	void PatchParent(NodeType*, NodeType*, NodeType*);
	bool deleteNode(string);
	bool operateOnNode(string, char, int);
	NodeType* searchForNode(string);
private:
	NodeType *RootPtr;
};
BinaryTreeClass iTree; //Initialize a tree to hold all inventory values
//*****************************************************************************************************
BinaryTreeClass::BinaryTreeClass() {
		// Initialize the Root Ptr to NULL
	RootPtr = NULL;
}
//*****************************************************************************************************
bool BinaryTreeClass::insertNode(NodeType newNode){
		// Receives – A new node to insert into tree
		// Task - Insert a node into the tree
		// Returns - A bool to indicate operation success or failure
		// Declare variables used in process
	bool inserted = false;
	NodeType  *newPtr, *currPtr;
	newPtr = new(NodeType);   
		//First search the tree. If the node is found matching this ID, return false
	if (searchForNode(newNode.ID)->ID != "NOT FOUND") {
		return false;
	}
	else if (newPtr != NULL){
		newPtr->ID = newNode.ID;
		newPtr->Name = newNode.Name;
		newPtr->QOnHand = newNode.QOnHand;
		newPtr->QOnOrder = newNode.QOnOrder;  // 
		newPtr -> Lptr = NULL;   //        
		newPtr -> Rptr = NULL;   //        
		currPtr = RootPtr;
		while (inserted == false)
		{
			if (currPtr == NULL)
			{
				RootPtr = newPtr;
				return true;                          
			}                                           
			else                        
			{
				if (newPtr->ID < currPtr ->ID)
					if (currPtr->Lptr != NULL)
						currPtr = currPtr->Lptr;
					else
					{
						currPtr->Lptr = newPtr;
						return true;
					}
				else
					if (currPtr->Rptr != NULL)
						currPtr = currPtr->Rptr;
					else
					{
						currPtr->Rptr = newPtr;
						return true;
					}
			}
		}  
	}   
	return false;
}  
//*****************************************************************************************************
//*****************************************************************************************************
inline void BinaryTreeClass::PatchParent(NodeType *Newparnode, NodeType *parnode, NodeType *delnode){


	if (parnode == NULL)
		RootPtr = Newparnode;
	else
		if (parnode->Lptr == delnode)
			parnode->Lptr = Newparnode;
		else
			parnode->Rptr = Newparnode;
}
//*****************************************************************************************************
inline bool BinaryTreeClass::deleteNode(string IDtoSearch){


	// Declare required local pointers 
	NodeType *delnode, *parnode, *node1, *node2, *node3;
	// Declare a flag to indicate the node to be deleted  is found  
	bool found = false;
		// Set the pointers to start at the root
	delnode = RootPtr;
	parnode = NULL;
	// Search the tree until we find the node to be deleted or until there
	//  are no more nodes to examine
	while (found == false && delnode != NULL)
	{		 // Set flag to true if we find the node
		if (IDtoSearch == delnode->ID)
			found = true;
		else 	 // Otherwise keep track of the parent node and move down
				 // the appropriate branch of the tree 
		{
			parnode = delnode;
			if (IDtoSearch < delnode->ID)
				delnode = delnode->Lptr;
			else
				delnode = delnode->Rptr;
		}
	}
	//  CASE 1 – Node is not in tree
	if (found == false) {
		return false;
	}
	else{
		if (delnode->Lptr == NULL)
			if (delnode->Rptr == NULL) // CASE 2 – Node has NO children
				PatchParent(NULL, parnode, delnode);
			else  	 	     // CASE 3 – Node has ONE right child 
				PatchParent(delnode->Rptr, parnode, delnode);
		else
		{
			if (delnode->Rptr == NULL)  // CASE 4 – Node has ONE left child    
				PatchParent(delnode->Lptr, parnode, delnode);
			else { 		     // CASE 5 – Node has TWO children
				node1 = delnode;
				node2 = delnode->Lptr;
				node3 = node2->Rptr;
				while (node3 != NULL) {
					node1 = node2;
					node2 = node3;
					node3 = node3->Rptr;
				}
				if (node1 != delnode) {
					node1->Rptr = node2->Lptr;
					node2->Lptr = delnode->Lptr;
				}
				node2->Rptr = delnode->Rptr;
				PatchParent(node2, parnode, delnode);
			}  /* end else */
		} /* end else  */
		return true;
	} /* end else */
}  // end function


//*****************************************************************************************************
//*****************************************************************************************************
inline bool BinaryTreeClass::operateOnNode(string IDtoSearch, char operation, int value) {
		//Receives – The ID of the node to operate on, the type of operation, and the op value
		//Task - Operate on an individual node
		//Returns - A bool indicating whether operation was successful
	NodeType *node = new(NodeType);
	node = searchForNode(IDtoSearch);
	if (node->ID == "NOT FOUND") { //If the node was not found in the search, return false;
		return false;
	}
	else { //If the node was found, perform the specified operation
		if (operation == 'P') { //If the operation is a 'P' Print the node
				//Print a header for the item
			dataOUT << "	Item             Item                    Quantity       Quantity" << endl;
			dataOUT << "	ID Number        Description             On hand        On Order" << endl;
			dataOUT << "--------------------------------------------------------------------" << endl;
				//Print the item
			dataOUT << "    " << left << setw(17) << node->ID  << setw(22) << node->Name
			 << right << setw(7) << node->QOnHand << setw(15) << node->QOnOrder << endl;
			dataOUT << "--------------------------------------------------------------------" << endl;
			lineCount += 5; //Increment the line counter
		}//If the operation is an 'S', adjust the inventory to reflect a sale
		else if (operation == 'S') { 
			node->QOnHand -= value;
		}//If the operation is an 'R', adjust the inventory to reflect a shipment received
		else if (operation == 'R') { 
			node->QOnOrder -= value;
			node->QOnHand += value;
		}//If the operation is an 'O', adjust the inventory to reflect a restock transaction
		else if (operation == 'O') {
			node->QOnOrder += value;
		}
		return true; //Return true to indicate that the operation was successful
	}
}
//*****************************************************************************************************

inline bool BinaryTreeClass::printEntireTree(){
		//Print each node in the tree
	if (RootPtr == NULL) {
		dataOUT << "There are no inventory items to print" << endl;
		lineCount++;
	}
	else {
		printEachNode(RootPtr);
		return true;
	}
}
//*****************************************************************************************************
inline void BinaryTreeClass::printEachNode(NodeType *root) {
		//Receives – The pointer to a node in the tree
		//Task - Print each node in the tree
		//Returns - Nothing
	if (root != NULL) {
		printEachNode(root->Lptr); //Recursively call left pointers
			//Print the contents of the current node
		dataOUT << "    " << left << setw(17) << root->ID  << setw(22) << root->Name 
			 << right << setw(7) << root->QOnHand << setw(15) << root->QOnOrder << endl;
		lineCount++; //Increment the line counter
		printEachNode(root->Rptr); //Recursively call right pointers
	}
}
//*****************************************************************************************************
//*****************************************************************************************************
inline NodeType* BinaryTreeClass::searchForNode(string IDtoSearch) {

	NodeType *currPtr = new(NodeType);

	currPtr = RootPtr;
	bool found = false;
	while (!found && currPtr != NULL) {
		if (IDtoSearch < currPtr->ID) {
			currPtr = currPtr->Lptr;
		}
		else if (IDtoSearch > currPtr->ID) {
			currPtr = currPtr->Rptr;
		}
		else if (IDtoSearch == currPtr->ID) {
			found = true;
		}
		
	}
	if (currPtr == NULL) {
		currPtr = new(NodeType);
		currPtr->ID = "NOT FOUND";
	}
	return currPtr;

}
//*****************************************************************************************************


#endif
