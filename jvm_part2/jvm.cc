#include "jvm.h"

/**
* convert string to number
*/
template <class T>
bool tryParse(T& t,const std::string& s)
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
		if(commandParts.at(0).compare(GOTO) == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: goto opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_goto(commandParts.at(1));
		} else if(commandParts.at(0).compare(IFEQ) == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: ifeq opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_ifeq(commandParts.at(1));
		} else if(commandParts.at(0).compare(IFNE) == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: ifne opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_ifne(commandParts.at(1));
		} else if(commandParts.at(0).compare(IFLT) == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: iflt opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_iflt(commandParts.at(1));
		} else if(commandParts.at(0).compare(IFGT) == 0)
		{
			// verify that an argument was given 
			if(commandParts.size() != 2)
			{
				cout << "ERROR: ifgt opcode expects one argument" << endl;
				exit(1);
			}

			this->jvm_ifgt(commandParts.at(1));
		} else if(commandParts.at(0).compare(INC) == 0)
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

	

void jvm::jvm_ifeq(string label)
{
int top1 = stackPtr->Pop();
if(top1==0)
goto(label);
}

//conditional jump 'not equal'
void jvm::jvm_ifne( string label)
{
int top1 = stackPtr->Pop();
if(top1!=0)
goto(label);

}
//conditional jump 'less than'
void jvm::jvm_iflt(string label)
{
int top1 = stackPtr->Pop();
int top2= stackPtr->Pop();
if(top2 < top1)  
{
	goto(label);
}
}
//conditional jump 'greater than'
void jvm::jvm_ifgt(string label)
{
int top1 = stackPtr->Pop();
int top2= stackPtr->Pop();
if(top2 > top1)
	goto(label);
}

void jvm::jvm_goto(string label)
{
std::map<std::string, unsigned int>::iterator position;
/*look for the label in the symbol table 
and assign the value ( index of the instruction ) to prog.counter
*/
position = symTable.find(label);
if(position != symTable.end())
{
   pc = position->second;
}
else
{   cout<<"Error:Invalid label"<<endl;
    //should we do something in this case?
    return;
}

}


void jvm::execute()
	{

	}
