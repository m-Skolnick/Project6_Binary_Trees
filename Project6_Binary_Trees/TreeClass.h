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
	NodeType searchTreeForNode(string, NodeType*);
	bool insertNode(NodeType);
	NodeType findNode(string);
	bool printEntireTree();
	void printEachNode(NodeType*);
	bool printNode(string);
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
inline NodeType BinaryTreeClass::searchTreeForNode(string IDtoSearch, NodeType *root)
{
	NodeType *nodeToReturn = new(NodeType);
	nodeToReturn->ID = "NOT FOUND";
	bool found = false;

	if (root != NULL) {
		if (!found) {
			searchTreeForNode(IDtoSearch, root->Lptr);
		}
		if (root->ID == IDtoSearch) {
			nodeToReturn = root;
			found = true;
		}
		if (!found) {
			searchTreeForNode(IDtoSearch, root->Rptr);
		}
	}
	return *nodeToReturn;
}
//*****************************************************************************************************
inline NodeType BinaryTreeClass::findNode(string IDtoSearch){

		//Search the tree for a node matching this ID
	return searchTreeForNode(IDtoSearch, RootPtr);
}

inline bool BinaryTreeClass::printNode(string IDtoSearch) {
	NodeType *nodeToPrint = new(NodeType);
	*nodeToPrint = findNode(IDtoSearch);
	if (nodeToPrint->ID == "NOT FOUND") {
		return false;
	}
	else {
		dataOUT << "    " << left << setw(17) << nodeToPrint->ID << setw(24) << nodeToPrint->Name
			<< setw(15) << nodeToPrint->QOnHand << nodeToPrint->QOnOrder << endl;

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


#endif
