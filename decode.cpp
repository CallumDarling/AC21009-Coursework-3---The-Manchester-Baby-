#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>


#define EMPTY_FILE					0	// there is no text in file
#define FILE_DOES_NOT_EXIST	        0 // can't find file


using namespace std;

vector< vector<int> > machineCode;
int accumulator[32] = {};
int control[32] = {};
int ci = 0;
int currentInstruction[32] = {};
int pi[32] = {};
int function = 0;
int operand = 0;
bool status = true;


void jmp(int);
void jrp(int);
void ldn(int);
void sto(int);
void sub(int);
void cmp();
void stp();



int load()
{
	string line = "";
	ifstream binaryFile;
	binaryFile.open("MachineCode.txt", ios::in);

	//error checking for file
	if (!binaryFile) //checks to see if file opens properly
	{
		cerr << "Error: Could not find the requested file.";
		return FILE_DOES_NOT_EXIST;
	}


	vector<int> row(0);
	// For every line
	while (!binaryFile.eof() && machineCode.size() <32)
	{
		getline(binaryFile, line);
		if (line.empty()) break;
		for (int i = 0; i<32; i++)
		{

			row.push_back(static_cast<int>(line[i]) - 48);
		}
		machineCode.push_back(row);
		row.clear();

	}


	binaryFile.close();

	return 0;
}

void output()
{
	vector< vector<int> >::const_iterator row;
	vector<int>::const_iterator col;

	for (row = machineCode.begin(); row != machineCode.end(); ++row)
	{
		for (col = row->begin(); col != row->end(); ++col)
		{
			cout << *col;
		}
		cout << endl;
	}
}


void fetch()
{
	cout << "\n===========================" << endl;
	ci++;
	output();
	cout << "\nCurrent Instruction = ";
	for (int i = 0; i < 32; i++)
	{
		currentInstruction[i] = machineCode[ci + 1][i];
		cout << currentInstruction[i];
	}
	cout << endl;
	cout << "Present Instruction = ";
	for (int i = 0; i <32; i++)
	{
		pi[i] = machineCode[ci][i];
		cout <<pi[i];
	}
	cout << endl;
}



void decode(vector<int> code)
{
	operand = (code[0]*1 + code[1]*2 + code[2]*4 + code[3]*8 + code[4]*16);
	

	function = (code[13]*1 + code[14]*2 + code[15]*4);

}

void execute()
{
	switch (function)
	{
	case 0:cout << " EXECUTING JMP-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		cout << "Set CI to content of memory location " << operand << endl;
		jmp(operand);
		break;
	case 1: cout << " EXECUTING JRP-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		jrp(operand);
		break;
	case 2: cout << " EXECUTING LDN-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		cout << "Load Accumulator with negative form of memory location " << operand << endl;
		ldn(operand);
		break;
	case 3: cout << " EXECUTING STO-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		cout << "Copy Accumulator to memory location " << operand << endl;
		sto(operand);
		break;
	case 4: cout << " EXECUTING SUB-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		cout << " subtract content of Memory location " << operand << " from Accumulator" << endl;

		sub(operand);
		break;
	case 5: cout << " EXECUTING SUB-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		cout << " subtract content of Memory location " << operand << " from Accumulator" << endl;
		sub(operand);
		break;
	case 6: cout << " EXECUTING CMP-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		cmp();
		break;
	case 7: cout << " EXECUTING STP-" << endl;
		cout << "operand: " << operand << endl;
		cout << "function: " << function << endl;
		stp();
		break;
	}

	cout << "===========================" << endl;
}

void jmp(int num)
{
	cout << " CI = ";
	for (int index = 0; index < 32; index++)
	{
		currentInstruction[index] = machineCode[num][index];
		cout << currentInstruction[index];
	}
}

void jrp(int num)
{

}

void ldn(int num)
{
	int i;
	for (int index = 0; index < 32; index++)
	{
		accumulator[index] = machineCode[num][index];
	}

	int ones[32];

	for ( i = 0; i < 32; i++)
	{
		if (machineCode[num][i] == 1)
		{
			ones[i] = 0;
		}
		else if (machineCode[num][i] == 0)
		{
			ones[i] = 1;
		}
		
	}
	
	for (i = 31; i > 0; i--)
	{
		if (ones[i] == 1 )
			accumulator[i] = 0;
		else
		{
			accumulator[i] = 1;
			break;
		}
	}

	//puts binary into actual order and not reversed 
	//reverse(begin(accumulator), end(accumulator));
	cout << "Accumulator: ";
	for (int index = 0; index < 32; index++)
	{
		cout << accumulator[index];
	}
	cout << endl;
}

void sto(int num)
{

	for(int i = 0; i<32;i++)
	{
		machineCode[num][i] = accumulator[i];
	}

	cout << "Accumulator: ";
	for (int index = 0; index < 32; index++)
	{
		cout << accumulator[index];
	}
	cout << endl;
}

void sub(int num)
{
	int answer[32] = {};
	bool carry = false;

	for (int i = 0; i < 32; i++)
	{
		answer[i] = accumulator[i] - machineCode[num][i];
		
			if (carry > 0 && answer[i]==1)
		{
			answer[i] = answer[i] - 1;
		}

		if (answer[i] == -1)
		{
			answer[i] = answer[i] + 2;
			carry++;
		}

		
	}
	
	cout << "Accumulator: ";
	for (int index = 0; index < 32; index++)
	{
		accumulator[index] = answer[index];
		cout << accumulator[index];
	}
	cout << endl;
}

void cmp()
{

}

void stp()
{
	status = false;
}


int main()
{

	
	load();

		for (size_t  i = 0; i < machineCode.size(); i++)
		{
			fetch();
			decode(machineCode[ci]);
			execute();
			if (status == false) break;
			
		}

		cout << "\n===========================Halting Machine===========================" << endl;
	
	return 0;
}
