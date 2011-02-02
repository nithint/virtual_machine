#include "jvm.h"


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

jvm::jvm(void)
{
}


jvm::~jvm(void)
{
}

jvm::jvm(int sz, vector<string> instrs, map<string, unsigned int> symTable)
{
	this->stackPtr = new Stack(sz);
	// make new copy of the data structures
	this->instructions = vector<string>(instrs);
	this->symbolTable = map<string, unsigned int>(symTable);
}

jvm::jvm(int sz=1000)
{
	this->stackPtr = new Stack(sz);
}

void jvm::execute(vector<string> commandParts)
{
	if(!(commandParts.size() == 0))
	{
		if(commandParts.at(0).compare("goto") == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: goto opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_goto(commandParts.at(1));
		} else if(commandParts.at(0).compare("ifeq") == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: ifeq opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_ifeq(commandParts.at(1));
		} else if(commandParts.at(0).compare("ifne") == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: ifne opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_ifne(commandParts.at(1));
		} else if(commandParts.at(0).compare("iflt") == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: iflt opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_iflt(commandParts.at(1));
		} else if(commandParts.at(0).compare("ifgt") == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: ifgt opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_ifgt(commandParts.at(1));
		} else if(commandParts.at(0).compare("inc") == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 3)
			{
				cout << "ERROR: ifeq opcode expects two arguments" << endl;
				exit(1);
			}
			// convert the two args to numbers
			int n, x;
			if(tryParse(n, commandParts.at(1).c_str()))
			{
				if(tryParse(x, commandParts.at(2).c_str()))
				{
					// increment local var n by x
					this->jvm_inc(n,x);
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
	}

	void jvm::execute()
	{

	}