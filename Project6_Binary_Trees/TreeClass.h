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
	bool insert(NodeType);
	bool insertNode(NodeType);
	NodeType findNode(string);
	void printEntireTree();
	void printEachNode(NodeType*);
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

inline bool BinaryTreeClass::insert(NodeType newNode){

	NodeType *newPtr = new(NodeType);
	NodeType *StartPtr = new(NodeType);
	

	newPtr->ID = newNode.ID;
	newPtr->Name = newNode.Name;
	newPtr->QOnHand = newNode.QOnHand;
	newPtr->QOnOrder = newNode.QOnOrder;

	if (isEmpty()) { //If the tree is empty, place the node at the root and return true;
		RootPtr = newPtr;
		RootPtr->Lptr = NULL;
		RootPtr->Rptr = NULL;
		return true;
	}
	else if (findNode(newPtr->ID).ID == "NOT FOUND") {

		StartPtr = RootPtr;

		if (RootPtr->ID < newPtr->ID) {

		}
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

inline NodeType BinaryTreeClass::findNode(string IDtoSearch){
	NodeType *nodeToReturn = new(NodeType);
	nodeToReturn->ID = "NOT FOUND";



	return *nodeToReturn;
}
//*****************************************************************************************************

inline void BinaryTreeClass::printEntireTree(){

	printEachNode(RootPtr);
	
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

#endif
