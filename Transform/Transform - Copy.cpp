// Transform.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "ProcessTransform.h"
#include <iostream>
#include <sstream> 
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		if (argv[0])
			std::cout << "Usage: " << argv[0] << " <number>" << '\n';
		else
			std::cout << "Usage: <program name> <input> <command> <command> ..." << '\n';

		exit(1);
	}

	

	ProcessTransform transform;
	std::string result = transform.Execute(argc, argv);

	
	cout << "Done Testing" << "\n";

}
