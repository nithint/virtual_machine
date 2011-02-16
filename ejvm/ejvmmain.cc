#include "ejvm.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <vector>
#include <string>

using namespace std;
using std::cout;

/**
* convert string to number
*/
template <class T>
bool tryParse(T& t,const std::string& s)
{
	std::istringstream iss(s);
	return !(iss >> t).fail();
}

void trim(string& str)
{
	str.erase(str.find_last_not_of(" \t")+1);
	str.erase(0,str.find_first_not_of(" \t"));
}

/*
main function reads in command from file
*/
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " *.jvm" << endl;
		exit(1);
	}

	ifstream fin(argv[1]);

	if(!fin)
	{
		cout << "File " << argv[1] << " not found." << endl;
		exit(1);
	}

	// read in the file line by line
	string str, recentMethod;
	vector<string> instrs = vector<string>();
	map<string, unsigned int> symTable = map<string, unsigned int>();
	map<string, unsigned int> limits = map<string, unsigned int>();

	while(getline(fin,str))
	{
		vector<string> parts = vector<string>();
		trim(str);
		// skip over empty lines
		if(str.empty())
			continue;

		// tokenize line
		istringstream iss(str);
		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter<vector<string> >(parts));

		// skip over lines with only spaces
		if(parts.size() <= 0)
			continue;
		// check if line contains labels by checking if the first part contains a ':' char at end
		if(parts[0].at(parts[0].length()-1) == ':')
		{
			// add the label to symbol table 
			string label = parts[0].substr(0,parts[0].length()-1);
			symTable.insert(make_pair(label,instrs.size()));
			// strip off the label from the instruction
			// the new str starts at end of the label part and spans the whole string. 
			// using a longer length coz it will only get till end of the string
			str = str.substr(parts[0].length(),str.length());
		}
		else if(parts[0].compare(".method")==0)
		// check if line is a method 
		{
			recentMethod = parts[1];
			// set method index to current+2 to skip over the .method & .limit lines
			symTable.insert(make_pair(recentMethod, instrs.size()+2));
		}
		else if(parts[0].compare(".limit") == 0)
		// check if line is a limit line
		{
			int limit;
			if(tryParse(limit, parts[1]))
			{
				limits.insert(make_pair(recentMethod, limit));
			}
			else
			{
				cout << "Error: parsing limit of method " << recentMethod << "." << endl;
				exit(0);
			}
		}
		// add line to instructions
		instrs.push_back(str);
	}

	ejvm calc(100000, instrs, symTable, limits);
	calc.execute();
	return 0;
}
