//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  TreeClass.cpp                  ASSIGNMENT #: 6                              *
//*                                                                                                   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     :  *************NEED TO DO THIS***********************                    *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//*****************************************************************************************************
struct NodeType {
		// The structure "NodeType" holds each inventory file.
	int QOnHand, QOnOrder;
	string ID,Name;
	NodeType *lChild,*rChild,*parent;

};
class BinaryTreeClass {
public:
	BinaryTreeClass();
	bool isEmpty();
	bool insert(NodeType);
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
	if (isEmpty()) {
		newPtr = RootPtr;
	}

	newPtr->ID = newNode.ID;
	newPtr->Name = newNode.Name;
	newPtr->ID = newNode.QOnHand;
	newPtr->ID = newNode.QOnOrder;

	return false;
}
