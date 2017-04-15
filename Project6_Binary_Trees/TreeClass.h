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
class BinaryTreeClass {
public:
	BinaryTreeClass();
	bool isEmpty();
	void operateOnNode(string, char,int, NodeType*);
	bool updateNode(string,char,int);
	bool insertNode(NodeType);
	bool printEntireTree();
	void printEachNode(NodeType*);
	void searchForNode(string, NodeType*);
	bool searchTree(string);
	void PatchParent(NodeType*, NodeType*, NodeType*);
	bool deleteNode(string);

private:
	NodeType *RootPtr;
};
BinaryTreeClass iTree; //Initialize a tree to hold all inventory values
//*****************************************************************************************************
BinaryTreeClass::BinaryTreeClass() {
		// Initialize the start Ptr to NULL
	RootPtr = NULL;
}
//*****************************************************************************************************

//*****************************************************************************************************


inline bool BinaryTreeClass::isEmpty()
{
	if (RootPtr == NULL) {
		return true;
	}
	else {
		return false;
	}
}
//*****************************************************************************************************
bool BinaryTreeClass::insertNode(NodeType newNode){
	


	bool inserted = false;
	NodeType  *newPtr, *currPtr;
	newPtr = new NodeType;        //
	if (newPtr != NULL)
	{
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
inline void BinaryTreeClass::operateOnNode(string IDtoSearch,char operation,int value, NodeType *root){	

	if (root != NULL) {
		
		operateOnNode(IDtoSearch, operation,value, root->Lptr);//Recursively call for left pointers
		
		if (root->ID == IDtoSearch) {
			if (operation == 'P') {
				dataOUT << "    " << left << setw(17) << root->ID << setw(24) << root->Name
					<< setw(15) << root->QOnHand << root->QOnOrder;
				//Add a line of dashes after printing output message
				dataOUT << endl;
				dataOUT << "--------------------------------------------------------------------";
				dataOUT << endl;
				lineCount += 2; //Increment the line counter
			}
			else if (operation == 'S') {
				root->QOnHand -= value;
			}
			else if (operation == 'R') {
				root->QOnOrder -= value;
				root->QOnHand += value;
			}
			else if (operation == 'O') {
				root->QOnOrder += value;
			}
			nodeFound = true;
		}	

		operateOnNode(IDtoSearch, operation,value, root->Rptr);//Recursively call for right pointers
		
	}

}
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
inline bool BinaryTreeClass::updateNode(string IDtoSearch, char code, int value) {
	nodeFound = false;

	operateOnNode(IDtoSearch, code, value, RootPtr);
	if (nodeFound) {
		return true;
	}
	else {
		return false;
	}
}
//*****************************************************************************************************

inline bool BinaryTreeClass::printEntireTree(){

	printEachNode(RootPtr);
	return true;
	
}
//*****************************************************************************************************

inline void BinaryTreeClass::printEachNode(NodeType *root) {
	if (root != NULL) {
		printEachNode(root->Lptr);

		dataOUT << "    " << left << setw(17) << root->ID  << setw(24) << root->Name 
			<< setw(15) << root->QOnHand << root->QOnOrder << endl;
		printEachNode(root->Rptr);
	}
}
//*****************************************************************************************************

inline bool BinaryTreeClass::searchTree(string IDtoSearch) {

	nodeFound = false;
	searchForNode(IDtoSearch, RootPtr);
	if (nodeFound) {
		return true;
	}
	else {
		return false;
	}

}
//*****************************************************************************************************

inline void BinaryTreeClass::searchForNode(string IDtoSearch, NodeType *root){

	if (root != NULL) {
		searchForNode(IDtoSearch, root->Lptr);

		if (IDtoSearch == root->ID) {
			nodeFound = true;
		}
		searchForNode(IDtoSearch, root->Lptr);
	}

}
//*****************************************************************************************************


#endif
