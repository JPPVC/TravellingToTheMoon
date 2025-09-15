#ifndef __AGCS_JPPVC__
#define __AGCS_JPPVC__

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

#define __AGCS_DEBUG__

namespace agcs {


enum KeyTypeID { //quantity of args in other words child nodes
	ARG_1, ARG_2, ARG_3, UNVALID_TYPE = -1
};

enum KeyID { //the ID 
	 SP, DP, TP, STRING, USP, UDP, UTP,  //Tokens representing what is the token, its type
 	 IF, WHILE, ELSE, ELIF, //Tokens representing flow control and conditional branching
         BODY, EXPRESSION,
         ROUTINE, MACRO, NAME,
	 UNVALID_ID = -1
};

struct AstNode {
	std::vector<int> childrenIndex;
	int parentIndex;
};

class Keywords {
	public:
	bool found;
	virtual int typeId() {return KeyTypeID::UNVALID_TYPE;};
	virtual int id() {return KeyID::UNVALID_ID;}
	virtual bool searchForWord(std::string src) {return false;};
	virtual int argQuant() {return -1;}; //quantity of args the keyword needs
	virtual bool isArg(std::string src) {return false;};
	virtual std::string toStr() {return "EMPTY KEYWORD";};
};


class MacroWord : public Keywords,  public AstNode {
	public:
	int tagIndex;
	int bodyIndex;
	std::vector<int> argsIndex;

	bool searchForWord(std::string src)override {
                if(std::regex_search(src, std::regex("@macro"))) {
                       // std::cout << "true for @macro" << std::endl;
			return true;
                }
                
        	return false;
	}
	
	virtual int typeId() override {
		return KeyTypeID::ARG_1;
	}

	virtual int id() {
		return KeyID::MACRO;
	}
	virtual int argQuant()override {
		return 1;
	}

	virtual bool isArg(std::string str)override {
		return std::regex_match(str, std::regex("(?<=\").*(?=\")")); //is an arg around double quotes
	}

	virtual std::string toStr() {
		return "MACRO WORD";
	}
};


class Ast {

};


struct Token {
	int typeID, id, argQuant;
	Token(int typeID, int id, int argQuant) : typeID(typeID), id(id), argQuant(argQuant) {}
};

class TokenStream {

	private:

	std::vector<Token> stream;
	public:
	TokenStream() {}
	void charToTokens(std::string src) {
		//std::string remove = src;
		
		std::vector<std::unique_ptr<Keywords>> keywords;
		keywords.push_back(std::make_unique<MacroWord>(MacroWord{}));
		
		//std::cout <<  "before loop" << std::endl;
		
		for (int c=0; c<keywords.size(); c++) {
			
			if (keywords[c]->searchForWord(src)) {
				std::cout <<  "found" << std::endl;
				
				stream.push_back(Token {keywords[c]->typeId(), keywords[c]->id(), keywords[c]->argQuant()});
			}
		}
	}
};


class Scanner {

	private:

	public:

	std::string trimLine(std::string src) {
		std::stringstream stream;
		stream << regex_replace(src, std::regex("^[ \t]+|[ \t]+$|^[` `]+|[` `]+$"), "\n"); //remove tabs and spaces from the begging
		return stream.str();
	}

	std::stringstream trimComments(std::string src) {
		std::stringstream stream;
		stream << regex_replace(src, std::regex("#.*"), ""); //remove comments
		return stream;
	}

	

	Scanner (std::string src) {
		std::stringstream srcStream;
		srcStream << src;

		//std::stringstream acc;
		std::string newLine;
		
		TokenStream tokens{};
		
		#ifdef __AGCS_DEBUG__
		std::cout << "...TRIMMED SRC FILE..." << std::endl;
		#endif
		while (std::getline(srcStream, newLine)) {
			//std::cout << regex_replace(teste, spacesNtabs, "") << std::endl;
			std::stringstream acc;
			acc << trimLine(newLine) << std::endl;
			acc = trimComments(acc.str());
			tokens.charToTokens(acc.str());
			
		}
//		std::cout << acc.str() << std::endl;
		 #ifdef __AGCS_DEBUG__
       //         for (int c=0; c<acc.str().size(); c++) { 
	//		std::cout << "line:  {" << acc.str()[c]  << "}, " << std::endl;
        //         }
		#endif
	}

};

}
#endif
