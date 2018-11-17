#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

vector<vector<string>> AssemblyCode; 
vector<vector<string>> labelTable;
vector<string> MachineCode;


string convertOpCode(string operation);
bool checkLabel(string label);

int operandBinaryNum[5];
int bitBinary[32]={};

void decToBinary(string num)
{
    int binary = stoi(num);
    // counter for binary array
    int i = 0;

    while (binary > 0) {

        // storing remainder in binary array in reverse order (first index in array is last number)
        operandBinaryNum[i]= binary % 2;
		binary = binary / 2;
        i++;
    }

}

void decToBinary32Bit(string num)
{
    int binary = stoi(num);
    // counter for binary array
    int i = 0;

    while (binary > 0) {

        // storing remainder in binary array in reverse order (first index in array is last number)
        bitBinary[i]= binary % 2;
		binary = binary / 2;
        i++;
    }

}


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

bool checkLabel(string label)
{

	for(unsigned int i = 0; i < labelTable.size(); i++)
	{	

		if(labelTable.at(i).at(0) == label)
			return false;
	}
	return true;
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
		string opcode;
		string operand;

		if(AssemblyCode.at(i).at(0) == "START:")
		{

			do 
			{	
				if(AssemblyCode.at(i).at(0).find(':')!=string::npos)
				{
					if(checkLabel(AssemblyCode.at(i).at(0)))
					{

						vector<string> temp;
						temp.push_back(AssemblyCode.at(i).at(0));
						temp.push_back("BaBy");
						labelTable.push_back(temp);

					}

					opcode = convertOpCode(AssemblyCode.at(i).at(1));

					if(AssemblyCode.at(i).size() == 3)
					{

						operand = AssemblyCode.at(i).at(2);

						if(checkLabel(AssemblyCode.at(i).at(2)))
						{

							vector<string> temp;
							temp.push_back(AssemblyCode.at(i).at(2) + ':');
							temp.push_back("BaBy");
							labelTable.push_back(temp);

						}

					}
					else
					{

						operand = "00000";

					}

				}
				else
				{

					opcode = convertOpCode(AssemblyCode.at(i).at(0));

					if(AssemblyCode.at(i).size() == 2)
					{

						operand = AssemblyCode.at(i).at(1);


						if(checkLabel(AssemblyCode.at(i).at(1)))
						{

							vector<string> temp;
							temp.push_back(AssemblyCode.at(i).at(1)+ ':');
							temp.push_back("BaBy");
							labelTable.push_back(temp);

						}

					}
					else
					{

						operand = "00000";

					}

				}

				MachineCode.push_back(operand + "00000000" + opcode + "0000000000000000");

				i++;

			}while (AssemblyCode.at(i).at(0) != "END:");

			if(AssemblyCode.at(i).at(0) == "END:")
			{

				if(checkLabel(AssemblyCode.at(i).at(0)))
				{
					
					vector<string> temp;
					temp.push_back(AssemblyCode.at(i).at(0));
					temp.push_back("BaBy");
					labelTable.push_back(temp);

				}

				MachineCode.push_back("00000000000001110000000000000000");

			}

			// VARAIBLES
			for(unsigned int j = i +1;j<AssemblyCode.size();j++)
			{

				decToBinary32Bit(AssemblyCode.at(j).at(2));

				string binary;

				for (unsigned int m = 0; m<32;m++)
				{

					binary.assign(bitBinary[m]);	
					cout << bitBinary[m];

				}
				cout << endl;

				cout << "BINARY " << binary << endl;

				MachineCode.push_back(binary);



				for(unsigned int k =  0; k<labelTable.size(); k++)
				{

					if(AssemblyCode.at(j).at(0) == labelTable.at(k).at(0))
					{

						labelTable.at(k).at(1) = to_string(j);

					}

				}

			} 
		
		}
		
	}

}

void secondPass()
{

	for(unsigned int i = 0; i < MachineCode.size(); i++)
	{
		string temp = MachineCode.at(i);
		string check;
		check += temp.at(0);
		check += temp.at(1);
		check += temp.at(2);
		check += temp.at(3);
		check += temp.at(4);
		check += ':';

		if(checkLabel(check) == false)
		{

			//decToBinary(check);

			for(int j = 0; j <5;j++)
			{

				temp.at(j) = operandBinaryNum[j];

			}

			MachineCode[i] = temp;

		}

	}

}


string convertOpCode(string operation)
{

	string opCode;

	if (operation == "JMP")
	{

		opCode = "000";

	}
	else if (operation == "JRP")
	{

		opCode = "100";

	}
	else if (operation == "LDN")
	{

		opCode = "010";

	}
	else if (operation == "STO")
	{

		opCode = "110";

	}
	else if (operation == "SUB")
	{

		opCode = "101";

	}
	else if (operation == "CMP")
	{

		opCode = "011";

	}
		else if (operation == "STP")
	{

		opCode = "111";

	}
	else
	{

		cout << "Invalid Opcode" << endl;
		opCode = "666";

	}

	return opCode;


}


void displayMachineCode()
{

	for(unsigned int i = 0; i < MachineCode.size(); i++)
	{
		cout << MachineCode.at(i) << endl;
	}	

}

void displayLabelTable()
{
	for(unsigned int i = 0; i < labelTable.size(); i++)
	{	

		for(unsigned int j = 0; j < labelTable.at(i).size(); j++)
		{

			cout << labelTable.at(i).at(j) << " ";

		}

		cout << endl;
	}

}
int main()
{

	load();
	//printAssemblyCode();
	firstPass();
	secondPass();
	displayMachineCode();
	displayLabelTable();


}