/*
 * jc.h
 *
 *  Created on: Jan 23, 2011
 */
#include <string>
#include "stack.h"
#include <map>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;
using std::pair;
using std::make_pair;

class jc
{
public:
	jc(int sz);
	jc();
	virtual ~jc();

	//INSTR:p:Just print the tos without popping
	void printTOS();
	// div: pop two from stack and do integer division
	void jc_div();
	// mul: pop two from stack and multiply
	void jc_mul();
	// sub: pop two from stack and subtract
	void jc_sub();
	//INSTR:add:pop tos twice and adds the elements and push result onto tos
	void jc_add();
	//INSTR: load n:Load the local variable n onto the stack
	void jc_load(int n);
	//INSTR:store n:pop tos and store the value into local map at n
	void jc_store(int n);
	//INSTR :pop :Pop the element at tos and return
	int jc_pop();
	//INSTR: const x: push the const integer onto the stack ( bounds check performed by Stack's member fns)
	void jc_push(int x);
	// execute the given command
	virtual void execute(vector<string> commandParts);
	
	// array to store valid opcodes
	static string validOpCodes[];

private:
	Stack * stackPtr; //The Stack class provided
	//Local variable mapping container
	map<unsigned int, int> localVars;
	//{"const", "pop", "store", "load", "add", "sub", "mul", "div", "p" };
	/**
	 * array to store instructions
	 */
	vector<string> instructions;
};

string jc::validOpCodes[] = {"const", "pop", "store", "load", "add", "sub", "mul", "div", "p" };