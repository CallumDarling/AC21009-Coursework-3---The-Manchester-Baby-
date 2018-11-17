/**
 * Manchester Baby Assembler header file
 * Displays a progress bar whenever it is called in during execution of the conversion
 */
 
// Importing libraries
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

// variables for the progress and the progress bar string.
int progress=0;
string progressBar [100];


void header()
{
	cout << "<---------------------------------------------->" << endl;
	cout << ""<<" 	Manchester Baby Assembler" << endl;
	cout << "<---------------------------------------------->" << endl;
	cout << ""<<"	Computer Systems 2A:" << endl;
	cout << ""<<"	Architecture Fundamentals and Unix" << endl;
	cout << "" << endl;
	cout << ""<<"	Group 13" << endl;
	cout << "<----------------------------------------------> " << endl;

}

void displayProgress()
{
	cout << string(50, '\n');

	if (progress != 100)
	{
		cout << " Progress : " << progress << " %" << endl;
		cout << "<---------------------------------------------->" << endl;
		if((progress % 2) == 1)
		{
			progressBar[progress] = "|";
		}

		for (int index = 0; index < progress; index++)
		{
			cout << progressBar[index];
		}
		cout << "\n<---------------------------------------------> " << endl;
		progress++;
		usleep(200000);
	}
	else
	{
		cout << " Progress : " << progress << " %" << endl;
		cout << "<------------------------------------------------->" << endl;

		for(int index = 0; index < 50; index++)
		{
			cout << "|";
		}
		cout << "\n<--------------------------------------------------> " << endl;

	}
}