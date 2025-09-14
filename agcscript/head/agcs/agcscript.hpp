/*
	Compilador e Interpretador header only
	

*/


#ifndef __AGCS_JPPVC__
#define __AGCS_JPPVC__

#define __AGCS_SCRIPT__

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
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

class Word {
        public:
        std::string hold;
        Word(std::string hold) : hold(hold){
        
        }
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
	
	void pushData(std::vector<unsigned char> adata) {
		for (auto c = adata.begin(); c != adata.end(); c++) {
			this->data.push_back(*c);
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
	
	TokenNode(TokenTypeID typeID, std::vector<unsigned char> data) :typeID(typeID)  {
		for (std::vector<unsigned char>::iterator c = data.begin();
			c != data.end(); c++) {
			this->data.push_back(*c);
		}
	}
	TokenNode(TokenTypeID typeID) : typeID(typeID)  {}
	
};

//controlling the data of the TokenNode is done 100% through this class
class TokenTree {

	private:
	
	std::vector<TokenNode> nodePool;
	public:

//TODO set syntax word tree
	TokenTree(Word add) {
		TokenNode first;
		std::stringstream acc;
		
		for (int c=0; c<add.hold.size(); c++) {

		}
		nodePool.push_back(first);
	}

	void addNode(TokenNode add) {
		nodePool.push_back(add);
	}
	
	

};

class TokenStream {

};



class WordList {
	private:
	std::vector<Word> list;
	int index;
	
	public:
	
	bool getNextWord(Word &set) {
		if (index < list.size()) {
			set = list[index];
			index++;
			return true;
		}
		return false;
	}
	void add(std::vector<Word> add) {
		
		for (int c=0; c<add.size(); c++) {
			list.push_back(add[c]);
		}
	}
	void display() {
		std::cout << "WORD LIST {" << std::endl;
		for (int c=0; c < list.size(); c++) {
			std::cout << list[c].hold << std::endl;
		}
		std::cout << std::endl << "}";
	}
	
	WordList() : index(0) {}
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

/*
	bool newLine(NewLine stream, std::stringstream &send) {
		
		int charCtr = 0;
		for(int c=stream.offset; c<stream.stream.str().size(); c++) {
			//std::cout << "char" << get << std::endl;
			if (stream.stream.str()[c] == '\n') {
				stream.offset += charCtr;
				return true;
			}
			send << stream.stream.str()[c];
			std::cout << send.str() << std::endl;
			charCtr ++;
		}
		//std::cout << "MALFORMED NEW LINE ERROR" << std::endl;
		return false;  //make this throw exception
	}

*/
//instead of removing a character from a string stream expensive operation
//just create an index list of the next character ignoring spaces

//return false if line is just a comment so the rest of the string processing steps are ignored
	std::vector<Word> charToWord(std::string stream) {
//		std::cout << "tirm unuse" << std::endl;
		std::vector<Word> send;
		std::stringstream acc;
		bool inString = false;
		int spaceCtr=0;
		int charCtr=0;
		
		//std::cout << stream;
		for (int c=0; c < stream.size(); c++) {
			std::cout << "iter" <<std::endl;
			
			if (stream[c] != ' ' && stream[c] >= 33 && stream[c] <= 126) {  //check if its valid ASCII character
				if (stream[c] == '#') break;
				if (stream[c] == 34 && !inString) {
					inString = true;
				} else if(stream[c] == 34 && inString)  {
					inString = false;
				}
				acc << stream[c];

			} else {
				
				if (!acc.str().empty() && !inString) {
					send.push_back(Word{acc.str()});
					acc.str("");
				}
				if (inString) {
					acc << ' ';
				}
			}
			
		///acc.clear();
		}

		send.push_back(Word{acc.str()});
		return send;
	}


//nao gosto desse testes MUDAR
	bool onlyNewLine(std::string stream) {
		
		if (stream[0] == '\n') return true;
		return false;
	}
	
	Scanner(std::string src) {
		std::stringstream stream;
		stream << src;

	
		std::stringstream wordList;
		std::string newLine;
		WordList list;
		Word word;
//TURN CHARS INTO WORDS
		while (std::getline(stream, newLine)) {
			
			//std::cout << getNewLine.str() << std::endl;
			if (!newLine.empty()) {
	
				std::vector<Word> word;
				word = charToWord(newLine); //remove spaces from the begining and coments
					
				
				if(!word.empty()){
					list.add(word);
				}

				newLine.clear();
			}

		}
		#ifdef __AGCS_SCRIPT__
		list.display();
		#endif

//TURN WORDS INTO TOKENS
	
		while (list.getNextWord(word)) {
			
		}
	}
};

class Script {

	public:
	Script(std::string &run);

};

}
#endif



