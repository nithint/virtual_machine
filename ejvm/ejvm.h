#pragma once
#include "jvm.h"
#include <stack>

// instruction set additions for ejvm

#define INVOKE "invoke"
#define RETURN "return"
#define FETCH "fetch"
#define MAIN "main"

class ejvm :
	public jvm
{
public:
	// base class (jvm)
	typedef jvm super;
	ejvm(int sz, vector<string> instrs, map<string, unsigned int> symTable, 
		map<string, unsigned int> limits);
	~ejvm(void);
	
	// execute over the whole set of instructions
	virtual void execute();
protected:
	// call trace
	stack<string> fnCalls;
	// frame pointer
	unsigned int fp;
	// limit of local vars allowed in a subroutine
	map<string, unsigned int> limits;

	virtual void ejvm_invoke(string& label);
	virtual void ejvm_return();
	virtual void ejvm_fetch(unsigned int localVar, int index);
	virtual void execute(vector<string> commandParts);
	// get the value stored on stack at position fp+index
	virtual int ejvm_frame(int index);
	//INSTR: load n:Load the local variable n onto the stack
	// redefined to use stack instead of separate data structure
	virtual void jc_load(int n);
	//INSTR:store n:pop tos and store the value into local variable n
	// redefined to use stack instead of separate data structure
	virtual void jc_store(int n);
	//Increment instruction where n is local var and x is the amount to increment by
	virtual void jvm_inc(int n, int x);
};

