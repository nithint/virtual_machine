#include "ejvm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

/**
* convert string to number
*/
template <class T>
bool tryParse(T& t,const std::string& s)
{
	std::istringstream iss(s);
	return !(iss >> t).fail();
}


ejvm::~ejvm(void)
{
}

void ejvm::execute()
{
	unsigned int currentPC = 0;
	this->pc = 0;
	
	// invoke main
	string main = MAIN;
	this->ejvm_invoke(main);
	// set current pc to main method's position
	currentPC = this->pc;

	// keep going as long as there is some function to execute
	while(!this->fnCalls.empty())
	{
		// check that pc points to valid instruction
		if(this->pc < this->instructions.size())
		{
			// valid loc - execute instruction
			vector<string> parts = vector<string>();
			string instr = this->instructions.at(this->pc);

			// tokenize line
			istringstream iss(instr);
			copy(istream_iterator<string>(iss),
				istream_iterator<string>(),
				back_inserter<vector<string> >(parts));
			// execute
			this->execute(parts);
		}
		else
		{
			// out of bounds 
			cout << "Invalid instruction address " << this->pc << " referenced." << endl;
			exit(0);
		}
		// update program counter
		// if a branch instr was executed in previous step, then don't 
		// update pc, just use it
		if(this->pc == currentPC)
		{
			this->pc++;
			currentPC++;
		}
		else
		{
			currentPC = this->pc;
		}
	}
}

void ejvm::execute(vector<string> commandParts)
{
	if(!(commandParts.size() == 0))
	{
		if(commandParts.at(0).compare(INVOKE) == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: invoke opcode expects one argument" << endl;
				exit(1);
			}

			this->ejvm_invoke(commandParts.at(1));
		} else if(commandParts.at(0).compare(RETURN) == 0)
		{
			this->ejvm_return();
		} else if(commandParts.at(0).compare(FETCH) == 0)
		{
			// convert the two args to numbers
			int n, x;
			if(tryParse(n, commandParts.at(1).c_str()))
			{
				if(tryParse(x, commandParts.at(2).c_str()))
				{
					// increment local var n by x
					this->ejvm_fetch(n,x);
				}
				else
				{
					cout << "Error: argument 2 must be a number" << endl;
				}
			}
			else
			{
				cout << "Error: argument 1 must be a number" << endl;
			}
		}
		else
		{
			// TODO: must look into which functions need to be modified
			// to work with stack instead of localVars map
			super::execute(commandParts);
		}
}
}

	void ejvm::ejvm_invoke(string& method)
	{
		std::map<std::string, unsigned int>::iterator position;
		unsigned int subroutineIndex;
		// lookup method index
		position = this->symbolTable.find(method);
		if(position != this->symbolTable.end())
		{
			subroutineIndex = position->second;
		}
		else
		{   cout<<"Error:Invalid subroutine name"<<endl;
		return;
		}
		// get subroutine local vars limit
		unsigned int subroutineLimit;
		position = this->limits.find(method);
		if(position != this->limits.end())
		{
			subroutineLimit = position->second;
		}
		else
		{
			cout << "Error: no limit defined for subroutine " << method << endl;
			return;
		}

		// push return addr
		this->stackPtr->Push(this->pc + 1);
		// push frame pointer
		this->stackPtr->Push(this->fp);
		// set frame pointer
		this->fp = this->stackPtr->Get_top() -1;
		// allocate limit # of local vars for callee func
		for(int i = 0; i < subroutineLimit; i++)
		{
			this->stackPtr->Push(NULL);
		}
		// push the new subroutine call to call trace stack
		this->fnCalls.push(string(method));
		// finally, set pc to callee func
		this->pc = subroutineIndex;
	}
	void ejvm::ejvm_return()
	{
		int result=-1;
		// pop off callee's stack and store the result from callee
		// result is always the last item popped
		while(stackPtr->Get_top() > (this->fp+1))
			result = stackPtr->Pop();

		// set frame pointer
		this->fp = stackPtr->Pop();
		// set pc
		this->pc = stackPtr->Pop();
		// push the result on stack
		stackPtr->Push(result);
		// pop the function from the call trace stack
		this->fnCalls.pop();
	}

	void ejvm::ejvm_fetch(unsigned int localVar, int index)
	{
		int value = this->ejvm_frame(index);
		// storing into local var achieved by pushing onto top of stack
		// then calling store 
		this->jc_push(value);
		this->jc_store(localVar);
		
	}

	int ejvm::ejvm_frame(int index)
	{
		// retrieve fp + index
		int indexToGet = this->fp + index;
		if(indexToGet >= 0 && indexToGet < stackPtr->Get_top())
		{
			return this->stackPtr->Get_element(indexToGet);
		}
		else
		{
			cout << "Error: attempt to fetch invalid stack location" << endl;
			exit(0);
		}
	}

	void ejvm::jc_load(int n)
	{
		if(n < 0)
		{
			fprintf(stderr, "Error: variable index should be non-negative\n");
			return;
		}
		int value = this->ejvm_frame(n+1);
		this->jc_push(value);
	}

	void ejvm::jc_store(int n)
	{
		if(n < 0)
		{
			fprintf(stderr, "Error: variable index should be non-negative\n");
			return;
		}
		int index = fp+n+1;
		int value = stackPtr->Pop();
		stackPtr->Set_element(index,value);
	}

	void ejvm::jvm_inc(int n, int x)
	{
		if(n < 0)
		{
			fprintf(stderr, "Error: variable index should be non-negative\n");
			return;
		}
		int index = fp+n+1;
		stackPtr->Set_element(index, stackPtr->Get_element(index)+x);
	}

	ejvm::ejvm(int sz, vector<string> instrs, map<string, unsigned int> symTable,
		map<string, unsigned int> limits)
		: super(sz, instrs, symTable)
	{
		this->limits = limits;
		this->fnCalls = stack<string>();
	}