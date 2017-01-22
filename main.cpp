/******************************************************************************
//
// NAME:          Blake Larson
//
// HOMEWORK:      Project2
//
// CLASS:         ICS 212
//
// INSTRUCTOR:    Ravi Narayan
//
// DATE:          November 29, 2016
//
// FILE:          main.c
//
// DESCRIPTION:   This is the main function that uses a user-interface
//            	  for a bank database application. All functions are
//		  					in seperate files, but this is strictly menu based.
//
*****************************************************************************/

#include "header.h"

int main(int argc, char* argv[])
{
	int option, optionRev, accnum, nameloop, birthyear;
	char accname[100], address[100], nextline[2];

	// Make an instance of the llist class
	llist mylist("proj2.txt");

	option = 0;
	optionRev = 0;
	accnum = 0;
	nameloop = 0;
	birthyear = 0;

	// Next two lines needed because cin.getline doesn't take in the newline.
	// So we need to apend them after each call to the function.
	nextline[0] = '\n';
	nextline[1] = '\0';

	cout << "------------------------------------------" << endl;
  cout << "-Welcome to the Bank Database Application-" << endl;
  cout << "------------------------------------------" << endl;

	#ifdef DEBUGMODE
	{
		cout << "******************************************" << endl;
		cout << "***************DEBUG MODE*****************" << endl;
		cout << "******************************************" << endl;
    cout << "" << endl;
	}
	#endif

	while (option == 0)
	{
    cout << "------------------------------------------" << endl;
		cout << "------------------MENU--------------------" << endl;
    cout << "+----------------------------------------+" << endl;
		cout << "| 1)  Add a new record                   |" << endl;
		cout << "| 2)  Modify a record                    |" << endl;
		cout << "| 3)  Print a record                     |" << endl;
		cout << "| 4)  Print all the records              |" << endl;
		cout << "| 5)  Delete a record                    |" << endl;
		cout << "| 6)  Reverse all records                |" << endl;
		cout << "| 7)  Quit Program                       |" << endl;
		cout << "+----------------------------------------+" << endl;
		cout << "" << endl;

		cout << "Please enter an option" << endl;

		// Set of commands and assignment statements.
		// 1) Clear the buffer after taking in input.
		// 2) Resetting the value of common variable, for security purposes.
		cin >> option;
		cin.clear();
		cin.ignore(100000, '\n');
		accnum = 0;
		memset(accname, 0, 100);
		memset(address, 0, 100);
		birthyear = 0;
		nameloop = 0;

		switch (option)
		{
			case 1 :
	      cout << "------------Option 1 selected-------------" << endl;
				while(accnum <= 0)
				{
					cout << "What is the account number you want to add?" << endl;
					if(!(cin >> accnum)) //String or char inpu
					{
						cout << "***Please enter an integer***" << endl;
						cin.clear();
						cin.ignore(100000, '\n');
						accnum = 0;
					}
					else if(accnum <= 0) //Negative or zero
					{
						cout << "***Only positive integers***" << endl;
						accnum = 0;
					}
				 }

				while(nameloop == 0)
				{
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "What is the full name you want to add?" << endl;
					cin.getline(accname, 100);
					if(strlen(accname) > 1 && strlen(accname) <= 30)
					{
						nameloop = 1;
					}
					if(accname[strlen(accname)-1] == '\n')
					{
						accname[strlen(accname)-1] = '\0';
					}
				}

				getAddress(address, 100);
				if(address[strlen(address)-1] == '\n')
				{
					address[strlen(address)-1] = '\0';
				}

        while(birthyear <= 999 || birthyear > 9999)
        {
          cout << "What is the birth year you want to add?" << endl;
					cout << "Please format: YYYY" << endl;
					if(!(cin >> birthyear))
          {
						cout << "***Please enter an integer***" << endl;
						cin.clear();
						cin.ignore(100000, '\n');
						accnum = 0;
					}
					else
          {
            if(birthyear <= 999 || birthyear > 9999)
            {
            	cout << "***Birth years can only be 4 digits***" << endl;
            }
    			}
				}
				cin.clear();
				cin.ignore(100000, '\n');

				mylist.addRecord(accnum, accname, address, birthyear);
				break;

			case 2 :
	      cout << "------------Option 2 selected-------------" << endl;
	      while(accnum <= 0)
	      {
          cout << "What is the account number you want to modify?" << endl;
					if(!(cin >> accnum))
          {
						cout << "***Please enter an integer***" << endl;
						cin.clear();
						cin.ignore(100000, '\n');
						accnum = 0;
          }
					else if(accnum <= 0)
					{
						cout << "***Only positive integers***" << endl;
						accnum = 0;
					}
	      }
				cin.clear();
				cin.ignore(100000, '\n');
				getAddress(address, 100);
          if(address[strlen(address)-1] == '\n')
          {
            address[strlen(address)-1] = '\0';
          }

				mylist.modifyRecord(accnum, address);
        cout << "Press ENTER to continue" << endl;
        break;

			case 3 :
        cout << "------------Option 3 selected-------------" << endl;
        while(accnum <= 0)
        {
          cout << "What is the account number you want to print?" << endl;
					if(!(cin >> accnum))
					{
						cout << "***Please enter an integer***" << endl;
						cin.clear();
						cin.ignore(100000, '\n');
						accnum = 0;
					}
					else if(accnum <= 0)
					{
						cout << "***Only positive integers***" << endl;
						accnum = 0;
					}
        }
				mylist.printRecord(accnum);
				break;

			case 4 :
        cout << "------------Option 4 selected-------------" << endl;
				cout << mylist;
        break;

			case 5 :
        cout << "------------Option 5 selected-------------" << endl;
        while(accnum <= 0)
        {
          cout << "What is the account number you want to delete?" << endl;
					if(!(cin >> accnum))
					{
						cout << "***Please enter an integer***" << endl;
						cin.clear();
						cin.ignore(100000, '\n');
						accnum = 0;
					}
					else if(accnum <= 0)
					{
						cout << "***Only positive integers***" << endl;
						accnum = 0;
					}
        }
				mylist.deleteRecord(accnum);
        break;

			case 6 :
				cout << "------------Option 6 selected-------------" << endl;
				mylist.reverse();
				while(optionRev == 0)
				{
					cout << "-----------------------------------------" << endl;
					cout << "--------------Reverse Menu---------------" << endl;
			    cout << "+---------------------------------------+" << endl;
					cout << "| 8)  Print all records                 |" << endl;
					cout << "| 9)  Reverse all records               |" << endl;
					cout << "+---------------------------------------+" << endl;
					cout << "" << endl;
					cout << "Please enter an option" << endl;
					cin >> optionRev;

					if (optionRev == 8)
					{
							cout << mylist;
							optionRev = 0;
					}
					else if(optionRev == 9)
					{
							mylist.reverse();
					}
					else
					{
							cout << "*******Please enter a valid option!*******" << endl;
							cin.clear();
							cin.ignore(100000, '\n');
							optionRev = 0;
					}
				}
				option = 0;
				break;

			case 7 :
        cout << "------------Option 7 selected-------------" << endl;
        cout << "----Exitting Bank Database Application----" << endl;
				mylist.~llist();
				exit(1);

			default :
				cout << "*******Please enter a valid option!*******" << endl;

		}
		option = 0;
	}
	return 0;
}
