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

typedef class TokenStream TokenStreamS;
typedef struct TokenStruct Token;

const int maxArgQuant = 4;

//ad -> add 
//ads -> add value to storage
//aug -> increment one to value in memory
//bzf -> branch to fixed place in memory
//bzmf -> branch to fixed place in memory if accumulator register is 0
//ca , cae, caf -> mov conts of a mem location to the accumulator register
//ccs -> get value of memory store in acc register and jump by comparing
//com , -> (ver mais sobre)
//cs -> pegar e converter valor de um local de mem usando 1's complement e colocar no registro acc
//das -> dp add operation A,L a um par na memoria o que forma uma operacao dp + dp
//dca -> dp mover conteudo de par A,L para um local da memoria movendo dp para dp dp -> dp
//dcom -> not operation in the register pair A,L
//dcs -> mover o negativo de do valor dp representado pelo par A,L em um outro local da memoria
//ddoubl -> adicionar A,L a si mesmo
//dim -> decrementar de valor positivo na memoria ou incrementar valor negatiov
//double -> adiciona o registro A a si mesmo
//dtcb -> operacao relacionada os banks e efetua um jump
//
const std::array<std::string, 46> InstructionMatch = {
	"ad", "ads", "aug", "bzf", "bzmf", "ca", "ccs", "com"
}

enum KeyTypeID { //quantity of args in other words child nodes
	ARG_0, ARG_1, ARG_2, ARG_3, UNVALID_TYPE = -1, INSTRUCTION_ARG
};

enum KeyID { //the ID 
	 SP, DP, TP, STRING, USP, UDP, UTP,  //Tokens representing what is the token, its type
 	 IF, WHILE, ELSE, ELIF, //Tokens representing flow control and conditional branching
         BODY, EXPRESSION,
         ROUTINE, MACRO, NAME,
	 EXPR_ARG, INSTRUCTION,
	 UNVALID_ID = -1
};

class AstNode {

	public:
	Token token;
	std::vector<int> childrenIndex;
	int parentIndex;
	AstNode(Token token, std::vector<int> childrenIndex, int parentIndex) : token(token), childrenIndex(childrenIndex), parentIndex(parentIndex){}
	bool hasChild(int index) {
		for (int c=0; c<childrenIndex.size(); c++) {
			if (index == childrenIndex[c]) return true;
		}
		return false;
	}
};

class Ast {

	public:
	std::vector<AstNode> nodes;
	Ast(){}
	
	int addNode(AstNode node) {
		nodes.push_back(node);
		return nodes.size();
	}
	int addChildToNode(AstNode add, int to) {
		nodes.push_back(add);
		if (to < nodes.size()) {
			std::cout << "ILLEGAL node index detected" << std::endl;
			return -1;
		}
		nodes[to].childrenIndex.push_back(nodes.size());
		return nodes.size();
	}
	void addChildToNode(int add, int to) {
		if (add > nodes.size() || to > nodes.size()) {
			std::cout << "ILLEGAL node index detected" << std::endl;
			return;
		}
		if (!nodes[to].childrenIndex.hasChild(add)) {
			nodes[to].childrenIndex.push_back(add);
		} else {
			std::cout << "ILLEGAL node index already added as child" << std::endl;
			return;
		}
	}
};

class Keywords {
	private:
	TokenStreamS *ref;

	public:

	bool found; 
	Keywords(TokenStreamS *ref) : ref(ref) {}
	virtual int typeId() {return KeyTypeID::UNVALID_TYPE;};
	virtual int id() {return KeyID::UNVALID_ID;}
	virtual bool searchForWord(std::string src) {return false;};
	virtual int argQuant() {return -1;}; //quantity of args the keyword needs
	virtual bool isArg(std::string src) {return false;};
	virtual std::string toStr() {return "EMPTY KEYWORD";};
	virtual std::string word() {return "__UNVALID__";};
	virtual std::vector<Token> findArgs(std::regex expr) {};
};

class InstructionWord : public Keywords, public AstNode {
	public:
	virtual int typeId() {
		return KeyTypeID::INSTRUCTION_ARG;
	}
	virtual int id() {
		return KeyID::INSTRUCTION;
	}
	virtual bool searchForWord(std::string src) {
		
	}
};

class RoutineWord : public Keywords, public AstNode {
	public:
	virtual int typedId()override {
		return KeyTypeID::ARG_3;
	}
	virtual int id()override {
		return KeyID::ROUTINE;
	}
	virtual std::vector<Token> findArgs(std::string str, std::regex expr) override{
		std::vector<Token> send;
		std::smatch match;
		
		std::regex_search(src, match, expr);
		
		for (int c=0; c<match.size(); c++) {
			send.push_back(Token {KeyTypeID::ARG_0, KeyID::EXPR_ARG} );
		}
		return send;
		
	}
	virtual bool searchForWord(std::string src)override {

		if (!syntaxAnalyze(src)) {
			std::cout << "SYNTAX ERROR WHILE declaring routine" << std::endl
			return false;
		}

		
		std::vector<Token> args = findArgs(src, std::regex("(?<=\().*(?=,).*(?=\))"));
	
		if (args[0].id == KeyID::UNVALID_ID) {
			std::cout << "Unable to find args for 'rot' keyword..." << std::endl;
			return false;
		}
		
		
		return true;
	}
	virtual int argQuant()override {
		return 3; //tag, args, body
	}
	bool syntaxAnalyze(std::string src) {

		if (std::regex_search(src, std::regex("rot")) {
			if (std::regex_search(src, std::regex("(?<=\().*(?=\))(.*(?=\{))"))) { //test routing arglist and opening bracket
				if (std::regex_search(src, std::regex("(?<=\().*(?=,).*(?=\))")) || std::regex_search(src, std::regex(""))) {// test if the args are correctly typed
				return true;
				}else {
					std::cout << "wrong formating in rot" << std::endl;
				}
			} else {
				std::cout << "wrong formating in rot" << std::endl;
			}
		}
		return false;
	}
	virtual bool isArg(std::string src)override {
		return std::s;
	}
};


class MacroWord : public Keywords,  public AstNode {
	public:
	int tagIndex;
	int bodyIndex;
	std::vector<int> argsIndex;

	bool searchForWord(std::string src)override {
                return std::regex_search(src, std::regex("@macro"));
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

	virtual std::string toStr()override {
		return "MACRO WORD";
	}
	virtual std::string word()override {
		return "@macro";
	}
};



struct TokenStruct {
	int typeID, id, argQuant;
	std::string word;
	TokenStruct(int typeID, int id, int argQuant, std::string word) : typeID(typeID), id(id), argQuant(argQuant), word(word) {}
};

class TokenStream {

	private:

	public:
	std::vector<Token> stream;
	TokenStream() {}
	void charToTokens(std::string src) {
		//std::string remove = src;
		
		std::vector<std::unique_ptr<Keywords>> keywords;
		keywords.push_back(std::make_unique<MacroWord>(MacroWord{this}));
		keywords.push_back(std::make_unique<RoutineWord>(RoutineWord{this}));

		//std::cout <<  "before loop" << std::endl;
		
		for (int c=0; c<keywords.size(); c++) {
			
			if (keywords[c]->searchForWord(src)) {
				std::cout <<  "found" << std::endl;
				
				stream.push_back(Token {keywords[c]->typeId(), keywords[c]->id(), keywords[c]->argQuant(), keywords[c]->word()});
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
