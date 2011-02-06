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
	// program counter
	unsigned int pc;
	// symbol table for branching
	map<string, unsigned int> symbolTable;
	
	//The unconditional jump instructions
    void  jvm_goto(std::string& label);
    //Conditional jump instr
    void jvm_ifeq(std::string& label);
    void jvm_ifne(std::string& label);
    void jvm_iflt(std::string& label);
    void jvm_ifgt(std::string& label);
    //Increment instruction
    void jvm_inc(int , int);


public:
	jvm(int sz, vector<string> instrs, map<string, unsigned int> symTable);
	~jvm(void);

	virtual void execute(vector<string> commandParts);
	// execute over the whole set of instructions
	virtual void execute();
};

