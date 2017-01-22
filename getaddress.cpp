/******************************************************************************
// Function name: getAddress
//
// DESCRIPTION:   A function that takes a string array and int as parameters
//		  						and is used to query for an address and stores them in
//                	a temp array which is then copied into the pushed array.
//
// Parameters:    param1: a char string array, that holds the entire empty
//			 						address container.
//		  					size: an integer value for the size of the address array
//
// Return values: n/a because it's void
//
*****************************************************************************/

#include "header.h"

void getAddress(char address[], int size)
{
	char temp[100];
	char temp2[100];
	char container[100];
	char nextline[2]; //Need to add a newline when using cin.get()
	int addressLoop;
	int addressLoop2;

	addressLoop = 0;
	addressLoop2 = 0;
	nextline[0] = '\n';
	nextline[1] = '\0';

	#ifdef DEBUGMODE
	{
		cout << "" << endl;
		cout << "***getAddress function called***" << endl;
		cout << "" << endl;
	}
	#endif

	cout << "What is the address you want to add?" << endl;
	cout << "Enter 'exit' when finished." << endl;
  memset(temp, 0, size);
  memset(temp2, 0, size);

	while(addressLoop == 0) {
		//fgets(temp, size, stdin);
		cin.getline(temp, 100);
		if(strcmp(temp, "exit") == 0)
		{
			addressLoop = 1;
		}
		else
		{
			strcat(temp, nextline); //No newline due to getline()
			strcat(temp2, temp);
		}
	}
	strcpy(address, temp2);
}
