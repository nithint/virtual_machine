#pragma once

#include <map>
#include <string>
#include "jc.h"

using namespace std;

class jvm :
	public jc
{

private:
	// program counter
	unsigned int pc;
	// symbol table for branching
	map<string, unsigned int> symbolTable;
public:
	jvm(int sz=1000);
	jvm(int sz, vector<string> instrs, map<string, unsigned int> symTable);
	jvm(void);
	~jvm(void);

	virtual void execute(vector<string> commandParts);
	// execute over the whole set of instructions
	virtual void execute();
};

