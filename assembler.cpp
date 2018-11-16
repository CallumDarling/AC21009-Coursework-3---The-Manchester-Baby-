#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<string>> AssemblyCode; 
vector<vector<string>> labelTable;
vector<string> MachineCode;


void load()
{

	string line;

	ifstream infile;

	// Open file as input
	infile.open("BabyTest1-Assembler.txt", ios::in);

	if(!infile)
	{

    	cout << "Error opening input file" << endl;
    	infile.close();

  	}
  	else
  	{

	  	while(!infile.eof())
		{

			// get next line in the file
			//getline(infile, line);

			getline(infile, line);

			if(!(line[0] == ';'))
			{

   				string buf;                 // Have a buffer string
    			stringstream ss(line);       // Insert the string into a stream

    			vector<string> tokens; // Create vector to hold our words

			    while (ss >> buf)
			    {

			    	if(buf == ";")
			    	{

			    		break;

			    	}

			        tokens.push_back(buf);

			    }

			    if(tokens.size() > 0)
			    {
					AssemblyCode.push_back(tokens);

				}

			}

		}

  		infile.close();

	}

}

void printAssemblyCode()
{

	for(unsigned int i = 0; i< AssemblyCode.size(); i++)
	{

		for(unsigned int j = 0; j<AssemblyCode.at(i).size(); j++)
		{

			cout << AssemblyCode.at(i).at(j) << " ";
		}

		cout << endl;
	}

}

void firstPass()
{

	if(AssemblyCode.at(0).at(0) != "VAR")
	{

		cout << "INVALID ASSEMBLY CODE." << endl;

	}
	else
	{

		MachineCode.push_back("00000000000000000000000000000000");

		int i = 1;

		if(AssemblyCode.at(i).at(0) == "START:")
		{
			
			do 
			{
				
				if(i == 1)
				{



				}


				i++;

				if(AssemblyCode.at(i).at(0) != "END:")
				{

					MachineCode.push_back("11100000000000000000000000000000");

				}

			}while (AssemblyCode.at(i).at(0) != "END:");
			
		}
		
	}

}

void displayMachineCode()
{

	for(unsigned int i = 0; i < MachineCode.size(); i++)
	{
		cout << MachineCode.at(i) << endl;
	}	

}

int main()
{

	load();
	printAssemblyCode();
	firstPass();
	displayMachineCode();


}