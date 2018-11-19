// Team 13
// Joel Sieber
// Alexander Arnaudov
// Patryk Jakubek
// Błażej Byczkowski
// Callum Darling


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


vector<vector<string>> AssemblyCode; 	// stores read in AssemblyCode without comments
vector<vector<string>> labelTable;		// stores labels and address.
vector<string> MachineCode;				// stores machine code of assembly code


string convertOpCode(string operation);	// convert opcode into binary
bool checkLabel(string label);			// check if label exists in label table
void printAssemblyCode();				// print AssemblyCode

string operandBinaryNum;	// store 5 bit binary
string bitBinary;			// store 32 bit binary

bool CodeValid = true;		// check if code is valid

/*

	Turns parameter into 5 bit binary

*/
void decTo5Binary(string num)
{	

	// convert num to int
    unsigned long long int binary = stoi(num);
    unsigned long long int c = 16;
   
   	// clear operandBInaryNum
   	operandBinaryNum = "";

   	// convert decimal to binary
    for(int i =0; i< 32; i++)
    {

        if(binary >= c)
        {

            operandBinaryNum += '1';
            binary -= c;

        }
        else
        {

            operandBinaryNum += '0';

        }

        c /=2;
    }

    // reverse the binary
    string temp;
    
    for(int i =4; i>=0; i--)
    {
        
        temp += operandBinaryNum[i];

    }

    operandBinaryNum = temp;

}

/*

	Turns parameter into 32 bit binary

*/
void decTo32Binary(string num)
{

    unsigned long long int binary = stoi(num);
    unsigned long long int c = 2147483648;

    bitBinary ="";
   
    for(int i =0; i< 32; i++)
    {

        if(binary >= c)
        {

            bitBinary += '1';
            binary -= c;

        }
        else
        {

            bitBinary += '0';

        }

        c /=2;
    }

    string temp;
    
    for(int i =31; i>=0; i--)
    {
        
        temp += bitBinary[i];

    }

    bitBinary = temp;

}

/*

	Load AssemblyCode without comments;

*/

void load()
{

	cout << "\n-------------------------------" << endl;
	cout << "\tLOADING ASSEMBLY CODE" << endl;
	cout << "-------------------------------\n" << endl;

	string line;
	ifstream infile;
	string filename;

	cout << "AVALIABLE TEXT FILES.\n" << endl;
	system("ls | grep .txt | cat");

	// ask for user input
	cout << "\nPlease enter name of file you want to convert to machine code." << endl;
	cin >> filename;
	filename += ".txt";

	// Open file as input
	infile.open(filename, ios::in);

	// if cant open
	if(!infile)
	{

		// output error
    	cout << "\nThe file does not exist." << endl;
    	infile.close();
    	CodeValid =false;

  	}
  	else
  	{

  		// while still lines to read
	  	while(!infile.eof())
		{

			// read line 
			getline(infile, line);

			// if line isnt a comment
			if(!(line[0] == ';'))
			{

				// store line in sstream
   				string buf;                 // Have a buffer string
    			stringstream ss(line);      // Insert the string into a stream

    			vector<string> tokens; 		// Create vector to hold our words

    			// while can push char onto buf
			    while (ss >> buf)
			    {

			    	// if its a comment
			    	if(buf == ";")
			    	{

			    		// stop
			    		break;

			    	}

			    	// push onto vector
			        tokens.push_back(buf);

			    }

			    // if token is not empty
			    if(tokens.size() > 0)
			    {	

			    	// push onto AssemblyCode
					AssemblyCode.push_back(tokens);

				}

			}

		}

  		infile.close();

  		cout << "\nLoading Complete.\n" << endl;
  		cout << "\nDisplaying Assembly Code:\n" << endl;
  		printAssemblyCode();
  		cout << "-------------------------------" << endl;

	}

}

/*
	
	Display Assembly Code

*/
void printAssemblyCode()
{

	for(unsigned int i = 0; i< AssemblyCode.size(); i++)
	{

		for(unsigned int j = 0; j<AssemblyCode.at(i).size(); j++)
		{

			cout << AssemblyCode.at(i).at(j) << "\t";
		}

		cout << endl;
	}

}

/*
	
	Check if label {parameter} exists

*/
bool checkLabel(string label)
{

	// check whole label table
	for(unsigned int i = 0; i < labelTable.size(); i++)
	{	

		// if exists
		if(labelTable.at(i).at(0) == label)
		{
		
			return false;
		
		}

	}

	return true;
}

/*
	
	First pass of assembly code

*/
void firstPass()
{

	cout << "\n-------------------------------" << endl;
	cout << "\tFirst Pass" << endl;
	cout << "-------------------------------\n" << endl;

	// if first line isnt not a VAR
	if(AssemblyCode.at(0).at(0) != "VAR")
	{	

		// display invalid code
		cout << "INVALID ASSEMBLY CODE." << endl;
		CodeValid = false;

	}
	else
	{

		// push 32 bit 0 onto MachineCode
		MachineCode.push_back("00000000000000000000000000000000");

		int i = 1;
		string opcode;
		string operand;

		// if next line is the start of code
		if(AssemblyCode.at(i).at(0) == "START:")
		{

			// do while not at "END:" label
			do 
			{	

				// if next line has label
				if(AssemblyCode.at(i).at(0).find(':')!=string::npos)
				{	
					// check if label was added onto label table before
					if(checkLabel(AssemblyCode.at(i).at(0)))
					{

						// push lable onto label table
						vector<string> temp;
						temp.push_back(AssemblyCode.at(i).at(0));
						temp.push_back(to_string(i));
						labelTable.push_back(temp);

					}

					// get opcode
					opcode = convertOpCode(AssemblyCode.at(i).at(1));

					// if line has 3 fields
					if(AssemblyCode.at(i).size() == 3)
					{

						// make field 3 the operand
						operand = AssemblyCode.at(i).at(2);

						// if not in label table
						if(checkLabel(AssemblyCode.at(i).at(2)))
						{	

							// push onto label table
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

					// make field 0 the operand
					opcode = convertOpCode(AssemblyCode.at(i).at(0));

					// if have 3 fields
					if(AssemblyCode.at(i).size() == 2)
					{

						// make field 2 the operand
						operand = AssemblyCode.at(i).at(1);

						// if operand is not in label tabel
						if(checkLabel(AssemblyCode.at(i).at(1)))
						{

							// push onto label table
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

				// push 32 bit balue onto machine code
				MachineCode.push_back(operand + "00000000" + opcode + "0000000000000000");

				i++;

			}while (AssemblyCode.at(i).at(0) != "END:" && static_cast<unsigned int>(i+1) <AssemblyCode.size());

			// if next label is END:
			if(AssemblyCode.at(i).at(0) == "END:")
			{

				// if not apart of the label table
				if(checkLabel(AssemblyCode.at(i).at(0)))
				{
					
					// push onto label table
					vector<string> temp;
					temp.push_back(AssemblyCode.at(i).at(0));
					temp.push_back(to_string(i));
					labelTable.push_back(temp);

				}

				// push code
				MachineCode.push_back("00000000000001110000000000000000");

			}
			else
			{

				cout << "No END Label" << endl;
				CodeValid = false;

			}

			// for all varaibles
			for(unsigned int j = i +1;j<AssemblyCode.size();j++)
			{

				// convert decimal value of varaible to 32 bit binary
				decTo32Binary(AssemblyCode.at(j).at(2));

				// push onto machine code
				MachineCode.push_back(bitBinary);

				// add address of labels inside label table
				for(unsigned int k =  0; k<labelTable.size(); k++)
				{

					if(AssemblyCode.at(j).at(0) == labelTable.at(k).at(0))
					{

						labelTable.at(k).at(1) = to_string(j);

					}

				}

			} 
		
		}
		else
		{

			cout << "Assembly Code Has No Start." << endl;
			CodeValid = false;

		}
		
	}

}

/*

	Second Pass of assembly code

*/
void secondPass()
{

	cout << "\n-------------------------------" << endl;
	cout << "\tSecond Pass" << endl;
	cout << "-------------------------------\n" << endl;

	// for each machine code
	for(unsigned int i = 0; i < MachineCode.size(); i++)
	{	
		// get first 5 values
		string temp = MachineCode.at(i);
		string check;
		check += temp.at(0);
		check += temp.at(1);
		check += temp.at(2);
		check += temp.at(3);
		check += temp.at(4);
		check += ':';

		// check if value is a label
		if(checkLabel(check) == false)
		{

			for(unsigned int k = 0; k< labelTable.size(); k++)
			{

				if(labelTable.at(k).at(0) == check)
				{
					
					// converts address of label into 5 bit
					decTo5Binary(labelTable.at(k).at(1));

					for(unsigned int j = 0; j <5;j++)
					{

						// replaces first 5 bits to label address
						temp.at(j) = operandBinaryNum[j];

					}

					// stores inside MachineCode
					MachineCode[i] = temp;

				}

			}

		}

	}

}

/*
	
	Return 3 bit binary opcode based on parameter

*/
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

		cout << "Invalid Opcode." << endl;
		opCode = "   ";
		CodeValid = false;

	}

	return opCode;


}

/*

	Display MachineCode

*/
void displayMachineCode()
{

	for(unsigned int i = 0; i < MachineCode.size(); i++)
	{

		cout << MachineCode.at(i) << endl;

	}	

}
/*
	
	Display Label Tabel

*/
void displayLabelTable()
{

	for(unsigned int i = 0; i < labelTable.size(); i++)
	{	

		for(unsigned int j = 0; j < labelTable.at(i).size(); j++)
		{

			cout << labelTable.at(i).at(j) << "\t";

		}

		cout << endl;
	}

}

/*
	
	Check if MachineCode is Valid

*/
void checkMachineCode()
{

	// if machineCode is greater than 32 x32 bits or less than 1 x32 bits
	if(MachineCode.size() > 32 || MachineCode.size() <1)
	{

		cout << MachineCode.size() << endl;
		CodeValid = false;

	}
	else
	{

		// check if Machine Code is all 1 and 0s
		for(unsigned int i = 0;i <MachineCode.size(); i++)
		{

			for(unsigned int j = 0; j< 32 ; j++)
			{

				if(MachineCode.at(i)[j] != '0' && MachineCode.at(i)[j] != '1')
				{
					cout << MachineCode.at(i)[j] << endl;
					CodeValid = false;

				}

			}

		}

	}

}


/*
	
	Save Machine Code

*/
void saveMachineCode()
{	

	cout << "\n-------------------------------" << endl;
	cout << "\tSAVING MACHINE CODE" << endl;
	cout << "-------------------------------\n" << endl;

	ofstream outfile;
	string filename;

	// ask for user input
	cout << "Please enter save file name:" << endl;
	cin >> filename;
	filename += ".txt";

	outfile.open(filename, ios::out);

	cout << "\nSaving to: " << filename << endl;

	// write Machine Code into file
  	for(unsigned int i =0; i< MachineCode.size(); i++)
  	{

  		outfile << MachineCode[i] << endl;

  	}


  	cout << "Saving Complete" << endl;
  	cout << "-------------------------------\n" << endl;

}

/*

	Truns Assembly Code into Machine Code

*/
void assembler()
{

	// load code
	load();

	// if valid
	if(CodeValid == true)
	{

		// make first pass
		firstPass();
		cout << "Displaying Label Tabel:\n" << endl;
		displayLabelTable();
			
		if(CodeValid == true)
		{

			cout << "\nDisplaying Machine Code:\n" << endl;
			displayMachineCode();

		}

		// if valid
		if(CodeValid == true)
		{

			// make second pass
			secondPass();

			if(CodeValid == true)
			{

				cout << "\nDisplaying Machine Code:\n" << endl;
				displayMachineCode();

			}

			// check if machinecode is valid
			checkMachineCode();

			if(CodeValid == true)
			{
				// save Machine Code
				saveMachineCode();
			
			}

		}
		else
		{

			cout << "\nInvalid Assembly Code" << endl;
			cout << "\nStopping Program." << endl;

		}	

	}
	else
	{

		cout << "\nInvalid Assembly Code" << endl;
		cout << "\nStopping Program." << endl;

	}

}

int main()
{

	assembler();

}
