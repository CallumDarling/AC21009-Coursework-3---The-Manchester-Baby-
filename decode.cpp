#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int machineCode[32][32]={};

void load()
{

	machineCode[32][32] ={};
	int row= 0;

	// create input file varaible
	ifstream infile;

	// Open file as input
	infile.open("MachineCode.txt", ios::in);

	string line;

	// For every line
	while(!infile.eof() && row <32)
	{

		// get next line in the file
		getline(infile, line);

		for(int i = 0; i<32; i++)
		{

			machineCode[row][i] = static_cast<int>(line[i]) - 48;

		}

		cout << endl;

		row++;

	}

	// close file
	infile.close();

	for(int i = 0; i<32; i++)
	{

		for(int j = 0; j<32; j++)
		{

			cout << machineCode[i][j];

		}

		cout << endl;

	}

}



int decode(int code[32])
{

	int operand = (code[0]*1 + code[1]*2 + code[2]*4 + code[3]*8 + code[4]*16);
	cout << "OPERAND: " << operand << endl;

	int function = (code[13]*1 + code[14]*2 + code[15]*4);
	cout << "FUNCTION: " <<  function << endl;

}


int main()
{
	load();
	decode(machineCode[2]);

}