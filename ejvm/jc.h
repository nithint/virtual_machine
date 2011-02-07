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
	virtual void printTOS();
	// div: pop two from stack and do integer division
	virtual void jc_div();
	// mul: pop two from stack and multiply
	virtual void jc_mul();
	// sub: pop two from stack and subtract
	virtual void jc_sub();
	//INSTR:add:pop tos twice and adds the elements and push result onto tos
	virtual void jc_add();
	//INSTR: load n:Load the local variable n onto the stack
	virtual void jc_load(int n);
	//INSTR:store n:pop tos and store the value into local variable n
	virtual void jc_store(int n);
	//INSTR :pop :Pop the element at tos and return
	virtual int jc_pop();
	//INSTR: const x: push the const integer onto the stack ( bounds check performed by Stack's member fns)
	virtual void jc_push(int x);
	// execute the given command
	virtual void execute(vector<string> commandParts);

protected:
	Stack * stackPtr; //The Stack class provided
	// Local variable mapping container
	map<unsigned int, int> localVars;
	
	/**
	 * array to store instructions
	 */
	vector<string> instructions;
};