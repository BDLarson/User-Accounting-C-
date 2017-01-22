#ifndef LLIST_H
#define LLIST_H

#include <iostream>
using namespace std;

class llist
{
	private:
		record * 	start;
		char 	 		filename[16];
		int	 			readfile();
		int 	 		writefile();
		record *  reverse(record*);
		void	 		cleanup();

	public:
		llist();
		llist(char[]);
		~llist();
		int addRecord(int, char[ ], char[ ], int);
		int printRecord(int);
		int modifyRecord(int, char [ ]);
    void printAll();
    int deleteRecord(int);
    void reverse();
		friend ostream& operator<<(ostream&, llist &);
};

#endif
