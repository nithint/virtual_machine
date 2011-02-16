/*
 * jcmain.cc
 *
 *  Created on: Feb 15, 2011
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

	// main function: reads instructions from commandline one by one and executes them
int main(int argc, char *argv[])
{
	jc calc(1000);
	string command;

	while(!(command == "q"))
	{
		cout << "Enter a command (q to quit): ";
		getline(cin,command);

		// quit on q
		if(command.compare("q") == 0)
			exit(0);

		// if empty, continue
		if(command.length()==0)
			continue;
		
		vector<string> parts = vector<string>();

		// tokenize attributes
		istringstream iss(command);
		copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(parts));

		/*for(unsigned int i = 0; i < parts.size(); i++)
		{
			cout << parts.at(i) << endl;
		}*/
		
		calc.execute(parts);
	}

  return 0;
}