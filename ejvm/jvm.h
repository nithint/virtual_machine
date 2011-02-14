#pragma once

#include <map>
#include <string>
#include "jc.h"

//Instruction set for extended java calculator
 #define CONST "const"
 #define POP   "pop"
 #define STORE "store"
 #define LOAD  "load"
 #define ADD   "add"
 #define SUB   "sub"
 #define MUL   "mul"
 #define DIV   "div"
 #define P     "p"
 #define INC   "inc"
 #define GOTO  "goto"
 #define IFEQ  "ifeq"
 #define IFNE  "ifne"
 #define IFLT  "iflt"
 #define IFGT  "ifgt"


using namespace std;

class jvm :
	public jc
{

private:
	// base class (jc)
	typedef jc super;
protected:
	// symbol table for branching
	map<string, unsigned int> symbolTable;
	// program counter
	unsigned int pc;
	//The unconditional jump instructions
	virtual void  jvm_goto(std::string& label);
	//Conditional jump instr
	virtual void jvm_ifeq(std::string& label);
	virtual void jvm_ifne(std::string& label);
	virtual void jvm_iflt(std::string& label);
	virtual void jvm_ifgt(std::string& label);
	//Increment instruction where n is local var and x is the amount to increment by
	virtual void jvm_inc(int n, int x);


public:
	jvm(int sz, vector<string> instrs, map<string, unsigned int> symTable);
	~jvm(void);

	virtual void execute(vector<string> commandParts);
	// execute over the whole set of instructions
	virtual void execute();
};

