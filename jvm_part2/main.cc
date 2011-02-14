#include "jvm.h"
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

using std::cout;
using namespace std;

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
	string str;
	vector<string> instrs = vector<string>();
	map<string, unsigned int> symTable = map<string, unsigned int>();

	while(getline(fin,str))
	{
		// skip over empty lines
		if(str.length() == 0)
			continue;
		
		vector<string> parts = vector<string>();
		// tokenize line
		istringstream iss(str);
		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter<vector<string> >(parts));

		// check if line contains labels by checking if the first part contains a ':' char at end
		if(parts.size() > 0 && parts[0].at(parts[0].length()-1) == ':')
		{
			// add the label to symbol table 
			string label = parts[0].substr(0,parts[0].length()-1);
			symTable.insert(make_pair(label,instrs.size()));
			// strip off the label from the instruction
			// the new str starts at end of the label part and spans the whole string. 
			// using a longer length coz it will only get till end of the string
			str = str.substr(parts[0].length(),str.length());
		}
		// add line to instructions
		instrs.push_back(str);
	}

	jvm calc(100000, instrs, symTable);
	calc.execute();
	return 0;
}
