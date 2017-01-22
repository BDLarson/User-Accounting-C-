/******************************************************************************
//
// FILE:          dbfunctions.c
//
// DESCRIPTION:   These functions are used for database purposes only.
//		              When a menu option is selected one of these will be called.
//		              If these functions are called via debugmode, then messages
//		              will display with information regarding function called and
//		              parameters passed.
//
//                This is file contains the definitions of readfile and
//		 							writefile. Readfile is used to read in the textfile
//		  						"output.txt". The program will not read any other file
//		  						in if the name is different, unless changed in the main.
//		  						writefile will write a text file "output.txt" containing
//		  						the contents of the database.
//
//                New functions cleanup and reverse added as well as both
//                  constructors and destructor.
//
*****************************************************************************/

#include "header.h"

/******************************************************************************
// Function name: addRecord
//
// DESCRIPTION:   A function that takes two ints, and two
//                  char arrays. Allows the user to add a record with specifics
//                  like: name, address, birth year, and account number. All
//		              records added with similar year of birth, will be added
//		              after already existing ones, no matter how many exist.
//
// Parameters:    uaccountno: an integer value for the account number.
//                uname: a char array to hold the full name.
//                uaddress: a char array to hold the address.
//                uyob: an integer to hold the birth year.
//
// Return values: int (for now 0)
//
*****************************************************************************/

int llist::addRecord(int uaccountno, char uname[], char uaddress[], int uyob)
{
  struct record *currRecord, *prevRecord, *tempRecord;
  int exitCount;
  int numRecAdded;

  exitCount = 0;
  numRecAdded = 0;
  currRecord = start;
  prevRecord = NULL;

  /*Allocate space on the heap for tempRecord*/
  tempRecord = new record;

  /*Store parameters passed into individual members of tempRecord*/
  tempRecord -> accountno = uaccountno;
  strcpy(tempRecord -> name, uname);
  strcpy(tempRecord -> address, uaddress);
  tempRecord -> yearofbirth = uyob;
  tempRecord -> next = NULL;

  #ifdef DEBUGMODE
  {
    cout << "-------------------------------" << endl;
    cout << "***addRecord function called***" << endl;
    cout << "-------------------------------" << endl;
    cout << "***Account number passed***" << endl;
    cout << uaccountno << endl;
    cout << "" << endl;
    cout << "***Name passed***" << endl;
    cout << uname << endl;
    cout << "" << endl;
    cout << "***Address passed***" << endl;
    cout << uaddress << endl;
    cout << "" << endl;
    cout << "***Birth year passed***" << endl;
    cout << uyob << endl;
    cout << "-------------------------------" << endl;
  }
  #endif

  while(exitCount == 0)
  {
    /*Check whether list is empty or not*/
    if(currRecord == NULL)
    {
      start = tempRecord;
      tempRecord -> next = NULL;
      exitCount = 1;
      numRecAdded++;
    }
		/*Add new record to the next available spot*/
    else if(currRecord -> yearofbirth >= tempRecord -> yearofbirth &&
            currRecord -> next == NULL)
    {
		  currRecord -> next = tempRecord;
			tempRecord -> next = NULL;
			exitCount = 1;
      numRecAdded++;
    }
		/*Add new record to the current start link and shift down the existing list*/
    else if(currRecord -> yearofbirth < tempRecord -> yearofbirth &&
            prevRecord == NULL)
    {
			tempRecord -> next = currRecord;
			start = tempRecord;
			exitCount = 1;
      numRecAdded++;
    }
		/*Add new record in between the currRecord and prevRecord*/
    else if(currRecord -> yearofbirth < tempRecord -> yearofbirth &&
            prevRecord != NULL)
		{
			prevRecord -> next = tempRecord;
			tempRecord -> next = currRecord;
			exitCount = 1;
			numRecAdded++;
		}
    /*Move down the list*/
		else
		{
			prevRecord = currRecord;
			currRecord = currRecord -> next;
		}
  }

  #ifdef DEBUGMODE
	{
		cout << "Number of records successfully added: " << numRecAdded << endl;
	}
  #endif

	return 0;
}

/******************************************************************************
// Function name: printRecord
//
// DESCRIPTION:   A function that takes a pointer argument and int.
//		              Allows the user to specify an account record to print.
//		              If the program cannot find the account number then the
//		              number of records printed will be 0. All records with the
//		              same account number, will be printed in the order that
//		              they are sorted by in the list.
//
// Parameters:    theBeginning: start pointer argument
//		            uaccountno: an integer value for the account number.
//
// Return values: int (for now 0)
//
*****************************************************************************/

int llist::printRecord(int uaccountno)
{
	struct record *currRecord;
	int numPrintRec;

	currRecord = start;
	numPrintRec = 0;

  #ifdef DEBUGMODE
  {
		cout << "---------------------------------" << endl;
		cout << "***printRecord function called***" << endl;
		cout << "---------------------------------" << endl;
		cout << "***Account number to be printed***" << endl;
    cout << uaccountno << endl;
		cout << "---------------------------------" << endl;
	}
  #endif

  if(start != NULL)
  {
    while(currRecord != NULL)
    {
      if(currRecord -> accountno == uaccountno)
      {
				cout << "" << endl;
				cout << currRecord -> accountno << endl;
    		cout << currRecord -> name << endl;
    		cout << currRecord -> address << endl;
    		cout << currRecord -> yearofbirth << endl;
    		cout << "" << endl;
				numPrintRec++;
			}
      currRecord = currRecord -> next;
    }
  }

  #ifdef DEBUGMODE
	   if(numPrintRec != 0)
	   {
	      cout << "Number of records printed: " << numPrintRec << endl;
	   }
	   else if(numPrintRec == 0)
	   {
		    cout << "No matching records found!" << endl;
	   }
  #endif

	return 0;
}

/******************************************************************************
// Function name: modifyRecord
//
// DESCRIPTION:   A function that takes a int, and char array. Allows the
//                  user to specify an account to update the address. All
//                  records with similar account numbers will be updated
//                  with the new one. If no records with specified account
//                  number are found, then 0 records will be modified.
//
// Parameters:    uaccountno: an integer value for the account number.
//		            uaddress: a char array for the address specified.
//
// Return values: int (for now 0)
//
*****************************************************************************/

int llist::modifyRecord(int uaccountno, char uaddress[])
{
  struct record *currRecord;
	int numModRec;

  currRecord = start;
	numModRec = 0;

  #ifdef DEBUGMODE
  {
		cout << "-----------------------------------" << endl;
		cout << "***modifyRecord function called***" << endl;
		cout << "-----------------------------------" << endl;
    cout << "***Account number to be modified***" << endl;
    cout << uaccountno << endl;
    cout << "***New address to be added***" << endl;
    cout << uaddress << endl;
		cout << "-----------------------------------" << endl;
	}
  #endif

  if(start != NULL)
  {
    while(currRecord != NULL)
    {
      if(currRecord -> accountno == uaccountno)
      {
  		  strcpy(currRecord -> address, uaddress);
        numModRec++;
      }
      currRecord = currRecord -> next;
    }
  }

  #ifdef DEBUGMODE
  if(numModRec != 0)
  {
    cout << "Number of records printed: " << numModRec << endl;
  }
  else if(numModRec == 0)
  {
    cout << "No matching records found!" << endl;
  }
  #endif

	return 0;
}

/******************************************************************************
// Function name: printAll
//
// DESCRIPTION:   Allows the user to print all records on file.
//
// Parameters:    None
//
// Return values: None because it's void
//
*****************************************************************************/

void llist::printAll()
{
	struct record *currRecord;
	int numAllRec;

	currRecord = start;
	numAllRec = 0;

  #ifdef DEBUGMODE
  {
		cout << "-------------------------------------" << endl;
		cout << "***printAllRecords function called***" << endl;
		cout << "-------------------------------------" << endl;
	}
  #endif

	while(currRecord != NULL)
	{
		cout << currRecord -> accountno << endl;
    cout << currRecord -> name << endl;
    cout << currRecord -> address << endl;
    cout << currRecord -> yearofbirth << endl;
		cout << "" << endl;
		currRecord = currRecord -> next;
		numAllRec++;
	}

  #ifdef DEBUGMODE
	{
		cout << "Number of records printed: " << numAllRec << endl;
	}
  #endif
}

/******************************************************************************
// Function name: deleteRecord
//
// DESCRIPTION:  Allows for the user to specify what record to delete
//		              from the account number given. If any record has the same
//		              account as the specified one, then they will all get
//		              deleted. If no record is found matching the specified
//		              account number, then no record will be deleted.
//
// Parameters:   uaccountno: an integer value for the account number.
//
// Return values: int (for now 0)
//
*****************************************************************************/

int llist::deleteRecord(int uaccountno)
{
	struct record *currRecord, *prevRecord, *tempRecord;
  int numDelRec;

	numDelRec = 0;
	currRecord = start;
	prevRecord = NULL;

	#ifdef DEBUGMODE
  {
		cout << "----------------------------------" << endl;
		cout << "***deleteRecord function called***" << endl;
		cout << "----------------------------------" << endl;
    cout << "***Account number to be deleted***" << endl;
    cout << uaccountno << endl;
		cout << "----------------------------------" << endl;
	}
  #endif

	if(start != NULL)
	{
		while(currRecord != NULL)
		{
			if(currRecord -> accountno == uaccountno)
			{
				if(currRecord -> next == NULL)
				{
					/*Delete a record from the list with only one*/
					if(prevRecord == NULL)
					{
						start = NULL;
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						delete tempRecord;
						numDelRec++;
					}
					/*Delete a record thats at the end of the list*/
					else
					{
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						prevRecord -> next = currRecord;
						delete tempRecord;
            numDelRec++;
					}
				}
				else
				{
					/*Delete a record surrounded by other records*/
					if(prevRecord != NULL)
					{
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						prevRecord -> next = currRecord;
						delete tempRecord;
            numDelRec++;
					}
					/*Delete a record at start from a list with a next record*/
					else
					{
						start = currRecord -> next;
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						delete tempRecord;
            numDelRec++;
					}
				}
			}
			else
			{
				prevRecord = currRecord;
				currRecord = currRecord -> next;
			}
		}
	}
	else
	{
		cout << "There are no records left to delete!" << endl;
	}

  #ifdef DEBUGMODE
	if(numDelRec != 0)
	{
		cout << "Number of records deleted: " << numDelRec << endl;
	}
	else if(numDelRec == 0)
	{
		cout << "No matching records found!" << endl;
	}
  #endif

	return 0;
}

/******************************************************************************
// Function name: readfile
//
// DESCRIPTION:   This function is able to read from a textfile and properly
//                  store each line into their proper variable, which is then
//                  all passed to addrecord.
//
// Parameters:    None
//
// Return values: int
//
*****************************************************************************/

int llist::readfile()
{
	ifstream input(filename);
  const bool fileOpened = input.is_open();
  int tempAcc, tempYOB, currState, nameLength;
  int addressLine, addressLength, numReadIn;
	char *garbage;
  char tempName[100], tempAdr[100], inputRecord[300], can[100], nextLine[2];

	tempAcc = 0;
	tempYOB = 0;
  currState = 1;
  garbage = can;
  nameLength = 0;
	addressLine = 1;
	numReadIn = 0;
  nextLine[0] = '\n';
  nextLine[1] = '\0';

	#ifdef DEBUGMODE
  {
    cout << "-------------------------------------" << endl;
    cout << "***readfile function called***" << endl;
    cout << "-------------------------------------" << endl;
    cout << "***Name of file to be read***" << endl;
		cout << filename << endl;
    cout << "-------------------------------------" << endl;
		if(fileOpened == false)
		{
			cout << "***There was an error opening the file***" << endl;
		}
	}
	#endif

	if (input != NULL)
	{
    while(input.getline(inputRecord, 300))
		{
			if (currState == 1)
			{
				tempAcc = strtol(inputRecord, &garbage, 10);
				currState++;
			}
			else if(currState == 2)
			{
				nameLength = (strlen(inputRecord) - 1);
				if(inputRecord[nameLength] == '\n')
				{
					inputRecord[nameLength] = '\0';
				}
				strcpy(tempName, inputRecord);
				currState++;
			}
			else if(currState == 3)
			{
				addressLength = (strlen(inputRecord) - 2);
				if (addressLine == 1)
				{
          strcat(inputRecord, nextLine);
					strcpy(tempAdr, inputRecord);
					addressLine++;
				}
				else
				{
					strcat(tempAdr, inputRecord);
				}
      	if(inputRecord[addressLength+1] == '!')
      	{
					tempAdr[strlen(tempAdr) - 1] = '\0';
        	currState++;
        	addressLine = 1;
        }
			}
			else if(currState == 4)
			{
        tempYOB  = strtol(inputRecord, &garbage, 10);
				currState = 1;
				numReadIn++;
				addRecord(tempAcc, tempName, tempAdr, tempYOB);
			}
			else
			{
				cout << "***There was an error!***" << endl;
			}
		}
	  input.close(); /*Closes the buffer*/
	}

	#ifdef DEBUGMODE
	{
		cout << "Number of records read from file: " << numReadIn << endl;
	}
	#endif
}

/******************************************************************************
// Function name: writefile
//
// DESCRIPTION:   This function is able to write the contents of the database
//                  into a textfile. Adds the delimiter "!" to the end of
//                  each record's address.
//
// Parameters:    None
//
// Return values: int
//
*****************************************************************************/

int llist::writefile()
{
	struct record *currRecord;
	int numWriteRec;
  ofstream output;

	currRecord = start;
	numWriteRec = 0;
  output.open(filename); /*Opens the buffer*/

	#ifdef DEBUGMODE
	{
	  cout << "-------------------------------------" << endl;
	  cout << "***writefile function called***" << endl;
	  cout << "-------------------------------------" << endl;
	  cout << "***Name of file to be written***" << endl;
	  cout << filename << endl;
	  cout << "-------------------------------------" << endl;
	}
  #endif

	while(currRecord != NULL)
	{
		output << currRecord -> accountno << endl;
    output << currRecord -> name << endl;
    output << currRecord -> address << "!" << endl;
    output << currRecord -> yearofbirth << endl;
		currRecord = currRecord -> next;
		numWriteRec++;
	}

	output.close(); /*Closes the buffer*/

	#ifdef DEBUGMODE
	{
		cout << "Number of records written to file: " << numWriteRec << endl;
	}
	#endif
}

/******************************************************************************
// Function name: llist (empty constructor)
//
// DESCRIPTION:   This is the empty constructor. Since no textfile is
//                  specified, "proj2.txt" will be the one read in. First
//                  the contents is copied to filename, then readfile is
//                  called.
//
// Parameters:    None
//
// Return values: None
//
*****************************************************************************/

llist::llist()
{
  #ifdef DEBUGMODE
  cout << "-------------------------------------" << endl;
  cout << "***llist constructor called***" << endl;
  cout << "-------------------------------------" << endl;
  #endif

  start = NULL;
  strcpy(filename, "proj2.txt");
  readfile();
}

/******************************************************************************
// Function name: llist (loaded constructor)
//
// DESCRIPTION:   This is the loaded constructor that has a specified
//                  textfile. The contents is then copied to filename and
//                  passed to the readfile function.
//
// Parameters:    None
//
// Return values: None
//
*****************************************************************************/

llist::llist(char input[])
{
  #ifdef DEBUGMODE
  cout << "-------------------------------------" << endl;
  cout << "***llist constructor called***" << endl;
  cout << "-------------------------------------" << endl;
  #endif

  start = NULL;
  strcpy(filename, input);
  readfile();
}

/******************************************************************************
// Function name: ~llist
//
// DESCRIPTION:   This function is able to end the program, by first writing
//                  the contents of the list to our text file and cleaning
//                  up the remains.
//
// Parameters:    None
//
// Return values: int
//
*****************************************************************************/

llist::~llist()
{
  #ifdef DEBUGMODE
  cout << "-------------------------------------" << endl;
  cout << "***llist destructor called***" << endl;
  cout << "-------------------------------------" << endl;
  #endif

  writefile();
  cleanup();
}

/******************************************************************************
// Function name: reverse (empty)
//
// DESCRIPTION:   This function is the wrapper class of the reverse function
//                  using recursion. Since we are not able to grab start from
//                  outside the class, we can use this function which calls
//                  start within it.
//
// Parameters:    None
//
// Return values: int
//
*****************************************************************************/

void llist::reverse()
{
  #ifdef DEBUGMODE
  cout << "-------------------------------------" << endl;
  cout << "***Reverse function (empty) called***" << endl;
  cout << "-------------------------------------" << endl;
  #endif

  if(start != NULL)
  {
    reverse(start);
  }
  else
  {
    cout << "No records to reverse!" <<endl;
  }
}

/******************************************************************************
// Function name: reverse (loaded)
//
// DESCRIPTION:   This function is able to reverse the enitre list using
//                  recursion. Takes in a record pointer, in this case start,
//                  which is used within the class.
//
// Parameters:    record pointer
//
// Return values: int
//
*****************************************************************************/

record* llist::reverse(record* pointer)
{
  struct record * currRecord;

  #ifdef DEBUGMODE
  cout << "-------------------------------------" << endl;
  cout << "***Reverse function (loaded) called***" << endl;
  cout << "-------------------------------------" << endl;
  #endif

  //One record base case
  if(pointer -> next == NULL)
  {
    currRecord = pointer;
    start = pointer;
  }
  else
  {
    currRecord = reverse(pointer -> next);
    pointer -> next = NULL;
    currRecord -> next = pointer;
    currRecord = pointer;
  }
  return currRecord;
}

/******************************************************************************
// Function name: cleanup
//
// DESCRIPTION:   This function is able to go through the link list and
//                  clear out any records that exist.
//
// Parameters:    None
//
// Return values: int
//
*****************************************************************************/

void llist::cleanup()
{
  struct record *currRecord;
  int numClean;

  currRecord = start;
  numClean = 0;

  #ifdef DEBUGMODE
  cout << "-------------------------------------" << endl;
  cout << "***Cleanup function called***" << endl;
  cout << "-------------------------------------" << endl;
  #endif

  if (start != NULL)
  {
    while(currRecord != NULL)
    {
      delete currRecord;
      currRecord = currRecord -> next;
      numClean++;
    }
    cout << "Number of records cleaned: " << numClean << endl;
  }
  else
  {
      cout << "No records to clean!" << endl;
  }
}

/******************************************************************************
// Function name: operator<<
//
// DESCRIPTION:   This overloads the << operation and replaces calling the
//                  printAll() method. Allows for us to call cout << on our
//                  complete link list llist instance.
//
// Parameters:    llist instance
//
// Return values: None
//
*****************************************************************************/

ostream & operator<<(ostream &output, llist &records)
{
  struct record *currRecord;
  int numAllRec;

  currRecord = records.start;
  numAllRec = 0;

  #ifdef DEBUGMODE
  {
    cout << "-------------------------------------" << endl;
    cout << "***printAllRecords function called***" << endl;
    cout << "-------------------------------------" << endl;
  }
  #endif

  while(currRecord != NULL)
  {
    cout << currRecord -> accountno << endl;
    cout << currRecord -> name << endl;
    cout << currRecord -> address << endl;
    cout << currRecord -> yearofbirth << endl;
    cout << "" << endl;
    currRecord = currRecord -> next;
    numAllRec++;
  }

  #ifdef DEBUGMODE
  {
    cout << "Number of records printed: " << numAllRec << endl;
  }
  #endif

  return output;
}
