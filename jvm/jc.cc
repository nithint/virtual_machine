/*
 * jc.cc
 *
 *  Created on: Jan 23, 2011
 */

#include "jc.h"
#include <iostream>

using namespace std;

jc::jc()
{
	// TODO Auto-generated constructor stub

}

jc::~jc()
{
	// TODO Auto-generated destructor stub
}

//Default constructor - note that the Stack class implementation does not specify a default stack size!
jc::jc(int sz=1000)
{
	this->stackPtr = new Stack(sz);
	//Check if the localvariable container can potentially accomodate all elements of the stack!
	/*if ( localVars.max_size() < sz )
		cout<<"warning: oversized stack!!" <<endl;//some specific warning/error stack size too big!!
	*/
}


//INSTR: const x: push the const integer onto the stack ( bounds check performed by Stack's member fns)
void jc::jc_push( int x)
{
	this->stackPtr->Push(x);
}


//INSTR :pop :Pop the element at tos and return
int jc::jc_pop()
{
	return stackPtr->Pop();
}

//INSTR:store n:pop tos and store the value into local map at n
void jc::jc_store(int n)
{
	int topElement;
	if(n < 0)
	{
		fprintf(stderr, "Error: variable index should be non-negative\n");
	}
	else
	{
		topElement = stackPtr->Pop();
		localVars.insert(make_pair(n, topElement));
	}
}



//INSTR: load n:Load the local variable n onto the stack
void jc::jc_load(int n)
{
	int  value;
	if(n<0)
	{
		fprintf(stderr, "Error: variable index should be non-negative\n");
	}
	else
	{
		map<unsigned int, int>::iterator it;

		// check if this localvar exists in map
		// find returns ptr to end of map on failure to find key
		it = localVars.find(n);
		if(it != localVars.end())
		{
			// localVar exists
			stackPtr->Push(it->second);
		}
		else
		{
			// localVar doesn't exist
			fprintf(stderr, "Error: local variable %d doesn't exist.", n);
		}
	}

}

//INSTR:add:pop tos twice and adds the elements and push result onto tos
void jc::jc_add()
{
	int top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	stackPtr->Push(top2+top1);
}

void jc::jc_sub()
{
	int top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	stackPtr->Push(top2-top1);
}

void jc::jc_mul()
{
	int top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	stackPtr->Push(top2 * top1);
}

void jc::jc_div()
{
	int top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	if(top1 == 0)
	{
		fprintf(stderr, "Error: division by zero attempted.");
	}
	else
	{
		stackPtr->Push(top2/top1);
	}
}

//INSTR:p:Just print the tos without popping
void jc::printTOS()
{
	if(stackPtr->Empty())
	{
		fprintf(stderr, "Error: stack is empty");
	}
	else
	{
		cout << "The topmost element is " << stackPtr->Get_top();
	}
}

//This fn reads and parses the command line
void readCmd()
{
	//TBD
}


