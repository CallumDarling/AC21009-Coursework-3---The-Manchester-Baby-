#include<iostream>
#include <string>
using namespace std;

 int binaryToDec(string );
 void decToBinary(string );

 string binary = "00011110";
 string decimal = "30";
 int binaryNum[10];

int main()
{

    cout<<"Converting decimal to binary: "<<endl;
    for(int i =0; i<binary.length();i++)
    {
        cout<<binary[i]<<" "<<endl;
    }

    cout<<"\nConverting binary to decimal: "<<endl;
    cout<<binaryToDec(binary);


}

 int binaryToDec(string num)
 {

        int number = stoi(num);
        int base = 1; //2 to the power of 0 is 1
        int decimal = 0;
        int lastDigit;

        while(number>0)
        {
             lastDigit= number%10;
            number/=10;

            decimal += lastDigit*base;

            base*=2;
        }

        return decimal;

 }

 void decToBinary(string num)
{
    int binary = stoi(num);
    // counter for binary array
    int i = 0;
    while (binary > 0) {

        // storing remainder in binary array in reverse order (first index in array is last number)
        binaryNum[i]= binary % 2;
		binary = binary / 2;
        i++;
    }
}
