/*
	Compilador e Interpretador header only
	Joao Pedro Protz Vicente

*/


#ifndef __AGCS_JPPVC__
#define __AGCS_JPPVC__


#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace agcs {

//instruction scheduling and register schedueling
class AGCVm {


};

//data types 
//SP -> Single Precision Number
//DP -> Double Precision number
//TP -> Triple Precision Number
//STRING -> alocated char array in the heap 
//USP -> unsigned Single Presicions Number
//UDP -> unsigned Double Precision Number
//UTP -> Unsigned Triple Precision Number

//flow control
//IF -> If expression boolean true then execute
// 	STATE = ScopeID
//	CHILD1 = EXPRESSION
//	CHILD2 = BODY
//	CHILD3(OPTIONAL) = ELSE or ELIF

//WHILE -> While boolean expression is true then execute
//	STATE = ScopeID
//	CHILD1 = EXPRESSION
//	CHILD2 = BODY

//ELSE -> Executed if if body is not executed
//	STATE = ScopeID
//	CHILD1 = BODY

//ELIF -> ELSE and IF , its only thre children are and EXPRESSION, a BODY and an ELSE or ELIF
//	STATE = ScopeID
//BODY
//	STATE = ScopeID
//	CHILD... -> can have as many children as needed 


//EXPRESSION -> its children are the following
// 	STATE = 0 or 1, boolean output
//	CHILD1 = ARG1
//	CHILD2 = operator
//	CHILD3 = ARG2

//ROUTINE -> A BODY with a tag associated to it
//	CHILD1 = BODY->STATE = 0
//	CHILD2 = NAME
//	CHILDX = ARGX
//	...

//MACRO -> Routine which builds code and runs at runtime
//	CHIDL1 = BODY->STATE = 0
//	CHILD2 = NAME
//	CHILDX = ARGX. (symbol)
//	...

//NAME
//	data = string
enum TokenTypeID {
	SP, DP, TP, STRING, USP, UDP, UTP,  //Tokens representing what is the token, its type
	IF, WHILE, ELSE, ELIF, //Tokens representing flow control and conditional branching
	BODY, EXPRESSION,
	ROUTINE, MACRO, NAME
};

class TokenNode {
	private:

	TokenTypeID typeID; //this index will determin the type of the Token and what its children are 
	int state;
	std::vector<unsigned char>data; //data held by the token
	
	std::vector<int> childID; // instead of a pointer you manipulate the 
	//child by using get and setfrom TokenTree all the nodes are stored only in the TokenTree tokenPool vector

	public:
	
	
	void setState(int state) {
		this->state = state;
	}
	
	void pushData(std::vector<unsigned char>data) {
		for (std::vector<unsigned char>::iterator c = data.begin();
			c !=data.end(); c++) {
			this->data.push_back(data[c]);
		}
	}
	void flushData() {
		data.clear();
	}

	void flushChild() {
		childID.clear();
	}
	
	void pushChild(int id) {
		childID.push_back(id);
	}
	
	TokenNode(std::string &stringID, TokenStateID typeID, std::vector<unsigned char> data) : stringID(stringID), typeID(typeID)  {
		for (std::vector<unsigned char>::iterator c = data.begin();
			c != data.end(); c++) {
			this->data.push_back(data[c]);
		}
	}
	TokenNode(std::string &stringID, TokenStateID typeID) : stringID(stringID), typeID(typeID)  {}
	
};

//controlling the data of the TokenNode is done 100% through this class
class TokenTree {

	private:
	
	std::vector<TokenNode> nodePool;
	public:
	TokenTree(TokenNode first) {
		nodePool.push_back(first);
	}

	void addNode(TokenNode add) {
		nodePool.push_back(first);
	}

};

class TokenStream {

};

class IndexedString {
	private:
	
	std::stringstream &data;
	std::vector<int> indexes;
	int top;

	public:
	IndexedString(std::stringstream &data) : data(data), top(0){}
	
	void resetTop() {
		top = 0;
	}
	
	std::string getWholeString() {
		std::stringstream stream;
		resetTop();
		for (char get : data) {
			stream << getNextChar();
		}
		stream << "\0";
	}
	char get(int virtualIndex) {
		return data[indexes[virtualIndex]];
	}
	char getNextChar() {
		return data[indexes[top]];
		top++;
	}
	
	void setNextChar(int index) {
		indexes.push_back(index);
	}
	
	void setSkip(int from, int to) {
		if (from < to) {  //this means there is only one char in the string
			setNextChar(from);
		} else {
			for (int c=from; c<to; c++) {
				setNextChar(c);
			}
		}
	}

};


//contato com todo a string
//How does this scanner work?
//Its meant for small scripts so I wont research in depth the best 
//lexical analyzer architecture I need to finish this today also -w-
//and a small set of reserver keywords and symbols, around 26, note this is trash I will gadly switch this for  
//a better solution

//0Add characters into words ->ignore spaces and null lines
//1.Detect if its a preprocessor stage
//	1.1Detect if its preprocessor macro
//		1.1.1 add to node list
//	1.2Detect if its a library load function

//2.Detect scope
//
class Scanner {

	public:

	bool newLine(std::stringstream &stream, std::stringstream &send) {
	
		for(char get : stream) {
			if (get == '\n') {
				return true;
			} else if (get == EOF || get == '\0') {
				return false;
			}
			send << get;
		}
	}


//instead of removing a character from a string stream expensive operation
//just create an index list of the next character ignoring spaces
	void trimUnused(std::stringstream &stream, IndexedString &indexed) {
		
		bool beginSet = false
		int beginSkipCtr = 0;
		int endSkipCtr = 0;
		char prev = 0;
		for (char get : stream) {

			if (get == ' ') {
				if ((prev == ' ' || prev == 0) && !beginSet) {
					beginSkipCtr++;
				} else {
					endSkipCtr++;
				}
			}
			if(get == '#') break;
		}
		
		indexed.setSkip(beginSkipCtr, endSkipCtr);
	}

//nao gosto desse testes MUDAR
	bool onlyNewLine(std::stringstream &stream) {
		if (stream[0] == '\n') return true;
		return false;
	}
	
	Scanner(std::string &src) {
		std::stringstream stream;
		stream << src;
		
		IndexedString indexed;
		std::stringstream getNewLine;
//while src file has new line
		while (newLine(stream, getNewLine)) {

			if (!getNewLine.str().empty() &&  !onlyNewLine(getNewLine)) {
				if (trimUnused(getNewLine, indexed)) { //remove spaces from the begining and coments
					std::cout << indexed.getWholeString() << std::endl;
				}
			}
		}
	}
};

class Script {

	public:
	Script(std::string &run);

};

}
#endif

