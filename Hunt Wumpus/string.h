#pragma once



/************************************************
DELETE THIS SECTION BEFORE FINAL SUBMISSION

This is a prototype class that should encapsulate
dynamic memory management of a character array.

It's functions should seek to take as much advantage
as possible of the <cstring> standard library.
strcpy, strcat, and strcmp will be especially useful.

The solutions for each of these functions are
about 3-5 lines. Remember, these functions may
be used by each other to greatly reduce the 
amount of work required (1 line solutions for many!)

Hint: Try implementing the 'resize' first. If you
keep most all of your dynamic memory management
to a single function, you can reuse it without
worrying about memory!

Note: It will be necessary for this class to
implement the C++ "Rule of 5" AND overload
stream operators for functionality with cin/cout.
Don't expect to solve these without research
or help!

IMPORTANT:
You should modify this header and implement
whatever additional functionality you find useful.

Modify this project until it compiles without error.
When successful, copy the string.h and string.cpp to
your game project.

YOU MAY CHANGE THE NAMESPACE IF YOU WISH,
but fix the test-main.


Final Hint:
If you hover-click on a green squiggly and select
"show potential fixes," one of them says
"Create definition in <filename>.cpp". You may use this
to automatically generate the function definitions
in the source file.
**************************************************/




/*************************************************
<FILL OUT THIS PORTION AND LEAVE IT IN YOUR FILE>
NAME OF FILE (ie. string.h)

DESCRIPTION OF WHAT THIS FILE DOES,
WHAT'S IN IT, AND HOW IT SHOULD WORK!
DUPLICATE THIS FOR THE SOURCE FILE.

Esmeralda Salamone, esmes@aie.edu.au, 9/23/2015
Modified: STUDENT NAME, EMAIL, DATE OF LAST EDIT

All rights reserved.
***************************************************/


// This header forward declares ostream and istream
// iostream should still be included in the source file
#include <iosfwd>

/*
The following comments describe implementation details
for each function. These comments are hints to you-
THEY SHOULD BE REMOVED and each function should have
a short comment describing what the function does.
*/
namespace sfw
{
	class string
	{
	private:
		char *m_data;	// Pointer to a dynamically allocated char array
		size_t m_size;	// How much data can our array currently store?

	public:	
		string(void); // Should set m_data and m_size to meaningful defaults

		string(size_t size); // create an empty string with a given amount of memory.
		string(const char *a, size_t size);
						// duplicate data in character array, and set our size to size.
		
		~string(); // should free (delete) dynamic memory if any is still in use (rule of 5).

		// Constructors, use strcpy
		string(const char *a);		// should duplicate the data of the character array
		string(const string &a);	// should duplicate the data of the other string (rule of 5).
		string(string &&a);			// should 'steal' the dynamic memory from the other string (rule of 5).

		// Assignment operators, use strcpy
		string &operator=(const char *a);	// should duplicate the data of the character array
		string &operator=(const string &a); // should duplicate the data of the other string (rule of 5).
		string &operator=(string &&a);		// should 'steal' the dynamic memory from the other string (rule of 5).

		// Concatenation assignment (resize and use strcat())
		string &operator+=(const string &a);
		string &operator+=(const char *a);
		string &operator+=(char a);

		// Array indexing
		char &operator[](size_t index);				// write access to an indexed character
		const char &operator[](size_t index) const; // read-only access to an indexed character

		size_t length() const;	// return the length of the string (strlen)
		size_t size() const;	// return the max number of chars we could hold (m_size-1, for term char)

		void resize(size_t size);	// create a new array of size, strcpy old data, then delete old data
		void clear();				// set the first character to '\0'
		bool empty() const;			// returns true if the first character is '\0'

		const char *cstring() const;	// constant access to m_data
	};

	// Relational operator overloads- use strcmp()
		// less-than is true if alphabetical-ascending
	bool operator<(const string &a, const string &b);
	bool operator<(const string &a, const char *b); 
	bool operator<(const char *a, const string &b);

	bool operator<=(const string &a, const string &b);
	bool operator<=(const string &a, const char *b);
	bool operator<=(const char *a, const string &b);
		// greater-than is true if alphabetical-descending
	bool operator>(const string &a, const string &b);
	bool operator>(const string &a, const char *b);
	bool operator>(const char *a, const string &b);

	bool operator>=(const string &a, const string &b);
	bool operator>=(const string &a, const char *b);
	bool operator>=(const char *a, const string &b);

	bool operator!=(const string &a, const string &b);
	bool operator!=(const string &a, const char *b);
	bool operator!=(const char *a, const string &b);

	bool operator==(const string &a, const string &b);
	bool operator==(const string &a, const char *b);
	bool operator==(const char *a, const string &b);

	// Concatenation operations- so many possible combinations.
		// should create a new string that is the concatenation of the two passed in.
		// Should support single characters also.
	string operator+(const string &a, const string &b);
	string operator+(const string &a, const char *b);
	string operator+(const char *a, const string &b);

	string operator+(const string &a, char b);
	string operator+(char a, const string &b);

	// Literal operator overload, use given char data to create a string
	// ie, "I AM A STRING"_sfw; should create a string /class/ literal!
	inline namespace literals {
		const string operator""_sfw(const char *a, size_t len); }

	// Allows us to work with stream processors (cin/cout)
	// they can be a little tricky! Don't be afraid to do research.
	std::ostream &operator<<(std::ostream &os, const string& p); //output stream operator
	std::istream &operator>>(std::istream &is, string& p); //input stream operator

}

