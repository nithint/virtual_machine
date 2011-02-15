/*
 * jc.cc for jvm
 *
 *  Created on: Fed 1, 2011
 */

#include "jc.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

/**
* convert string to number
*/
template <class T>
bool tryParse(T& t, 
				 const std::string& s)
{
  std::istringstream iss(s);
  return !(iss >> t).fail();
}


/** CONSTRUCTORS/DESTRUCTORS **/

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


void jc::execute(vector<string> commandParts)
{
	if(!(commandParts.size() == 0))
	{
		if(commandParts.at(0).compare("const") == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: const opcode expects one argument" << endl;
				exit(1);
			}
			// TODO: error checking needed for if argument is not a number
			int argument;
			if(tryParse(argument, commandParts.at(1).c_str()))
			{
				this->jc_push(argument);
			}
			else
			{
				cout << "Error: argument must be a number" << endl;
			}
		}
		else if(commandParts.at(0).compare("p") == 0)
		{
			this->printTOS();
		}
		else if(commandParts.at(0).compare("store") == 0)
		{
			if(commandParts.size() != 2)
			{
				cout << "Error: store opcode expects one argument" << endl;
				exit(1);
			}
			int argument;
			if(tryParse(argument, commandParts.at(1).c_str()))
			{
			this->jc_store(argument);
			}
			else
			{
				cout << "Error: variable should be non-negative" << endl;
			}
		}
		else if(commandParts.at(0).compare("load") == 0)
		{
			if(commandParts.size() != 2)
			{
				cout << "ERROR: load opcode expects one argument" << endl;
				exit(1);
			}
			// TODO: error checking for nan
			int argument;
			if(tryParse(argument, commandParts.at(1).c_str()))
			{
				this->jc_load(argument);
			}
			else
			{
				cout << "Error: variable index should be non-negative" << endl;
			}
		}
		else if(commandParts.at(0).compare("add") == 0)
		{
			this->jc_add();
		}
		else if (commandParts.at(0).compare("sub") == 0)
		{
			this->jc_sub();
		}
		else if (commandParts.at(0).compare("mul") == 0)
		{
			this->jc_mul();
		}
		else if (commandParts.at(0).compare("div") == 0)
		{
			this->jc_div();
		}
		else if (commandParts.at(0).compare("pop") == 0)
		{
			this->jc_pop();
		}
		else
		{
			// undefined command
			cout << "Illegal opcode" << endl;
		}
	}
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
		map<unsigned int, int>::iterator it;

		// check if this localvar exists in map
		// find returns ptr to end of map on failure to find key
		it = localVars.find(n);
		if(it == localVars.end())
		{
			// doesn't exist, create new
			localVars.insert(make_pair(n, topElement));
		}
		else
			localVars[n] = topElement;
	}
}



//INSTR: load n:Load the local variable n onto the stack
void jc::jc_load(int n)
{
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
	if(stackPtr->Size() < 2)
	{
		cout << "error: stack emtpy" << endl;
		return;
	}
	int top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	stackPtr->Push(top2+top1);
}

void jc::jc_sub()
{
	if(stackPtr->Size() < 2)
	{
		cout << "error: stack emtpy" << endl;
		return;
	}
	int top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	stackPtr->Push(top2-top1);
}

void jc::jc_mul()
{
	if(stackPtr->Size() < 2)
	{
		cout << "error: stack emtpy" << endl;
		return;
	}
	int top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	stackPtr->Push(top2 * top1);
}

void jc::jc_div()
{
	if(stackPtr->Size() < 2)
	{
		cout << "error: stack emtpy" << endl;
		return;
	}
	// check if divisior is zero before popping
	int top1 = stackPtr->Peek();
	if(top1 == 0)
	{
		fprintf(stderr, "Error: division by zero attempted.\n");
		return;
	}

	top1 = stackPtr->Pop();
	int top2 = stackPtr->Pop();
	stackPtr->Push(top2/top1);
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
		//cout << stackPtr->Pop();
		cout << stackPtr->Peek() << endl;
	}
}


