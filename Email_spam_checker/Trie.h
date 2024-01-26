#pragma once
/*

This project was done by:
Abdelrahman Ahmed Hamed       2022/03005
Mostafa Ayman Mostafa         2022/10504
Mostafa Waleed Zaki           2022/08461
Ramez Emad Ezzat              2022/01013
Yousef Ali Saied              2022/02675

*/
/*----------------------------------Trie.h-----------------------------------------------------------------

This header file defines the data structure Trie.
Basic operations:
Constructor
Destructor
isNextChar:        Check if the character is a child in a certain node
haveNextChar:      Check if a certain node is a parent of other nodes
isEmpty:           Check if the Trie is empty
insert:            Insert a string in the Trie
search:            Check if a certain string stored in the Trie
erase:             Removes a certain string from the Trie
clear:             Removes all the strings from the Trie when a root pointer is passed as a parameter
display:		   Display the contensts of this Trie.
displayAUX:        Recursion function used in display function.
indexOf:           Search for the index of ASCII character in the nextChar array
revIndOf:          Reverse of the indexOf function to use it in display
formatRegulator:   Changes the given string to be all lowercased
operator<<:        overloading operator for the output stream to display the contents of this Trie.
-----------------------------------------------------------------------------------------------------------*/

#include<iostream>
#include<string>
using namespace std;
enum severityLevel { Low = 5, Medium = 10, High = 15 };
typedef char ElementType;
class Trie
{
private:
	/****** Data Members ********/
	const static int charCount = 30;
	class trieNode {
	public:
		trieNode* nextChar[charCount] = { nullptr }; //Array of addresses to the nextChar
		bool isWord; //Determines if the current node the last character of a string
		trieNode* parent; //Pointer that points to the parent
		severityLevel spamWordSeverity; //Determines the severity of the spam word
		trieNode(trieNode* par) :isWord(false), parent(par), spamWordSeverity(Low) {}; //Constructor that intializes the isWord Variable as False
	};
	trieNode* root; //Pointer to the root node
public:
	typedef trieNode* NodePtr;
	/********* Function Members ***********/
	/***** Class Constructor *****/
	Trie();
	/*-----------------------------------------------------------------------------
	Constructs a Trie object.

	Precondition:  none
	Postcondition: An empty Trie object is constructed; root points to
	a node.
	-------------------------------------------------------------------------------*/
	/***** Class destructor *****/
	~Trie();
	/*-----------------------------------------------------------------------------
	Destroys a Trie object.

	Precondition:  The life of a Trie object is over.
	Postcondition: The memory dynamically allocated for the nodes are retrieved.
	-------------------------------------------------------------------------------*/
	/***** isEmpty operation *****/
	bool isEmpty() const;
	/*----------------------------------------------------------------------
	Check if a list is empty.

	Precondition:  none
	Postcondition: true is returned if the Trie is empty, false if not.
	-----------------------------------------------------------------------*/
	/***** insert operation *****/
	void insert(string, severityLevel);
	/*---------------------------------------------------------------------
	Inserts a string in the Trie

	Precondition:  String doesn't already exist in the Trie.
	Postcondition: String is inserted in the Trie marked with its severity level.
	-----------------------------------------------------------------------*/
	/***** search operation *****/
	bool search(string, severityLevel&) const;
	/*---------------------------------------------------------------------------------------------------------------
	Searches if a string exists in the Trie

	Precondition:  Trie isn't empty.
	Postcondition: returns True if the String exists and return the severity level by reference, and False otherwise.
	-----------------------------------------------------------------------------------------------------------------*/
	/***** erase operation *****/
	void erase(string);
	/*---------------------------------------------------------------------
	Erases a string from the Trie

	Precondition:  Trie is not empty and the string exists in the Trie.
	Postcondition: String is erased.
	-----------------------------------------------------------------------*/
	void display(ostream& out) const;
	/*--------------------------------------------------------------------
	 Display the contensts of this Trie.

	 Precondition:  ostream out is open
	 Postcondition: Elements of this list have been output to out.
	 --------------------------------------------------------------------*/
private:
	bool search(string) const; //overloaded function to be used inside the class
	void clear(NodePtr); //Erases all strings in the trie in a recursive manner
	bool isNextChar(ElementType, NodePtr) const; // Checks if a certain character exists in the nextChar map
	bool haveNextChar(NodePtr) const; // Checks if a certain node have nextChar or not
	int indexOf(ElementType) const; //Return the index of ASCII character in the nextChar array
	string formatRegulator(string) const; //Return the string is standard format
	char revIndOf(int) const;//Reverse of the indexOf function to use it in display
	void displayAUX(NodePtr ptr, ostream& out) const;//Recursion function used in display function.
}; //end of the Trie class

ostream& operator<<(ostream& out, const Trie& aTrie);//overloading operator for the output stream to display the contents of this Trie.