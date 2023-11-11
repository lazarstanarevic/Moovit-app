#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

class IndexOutOfRange : public exception {
public:
	IndexOutOfRange(const char* msg) : exception(msg) {}

	void print()
	{
		cout << this->what() << "\nMolimo Vas da ponovo izaberete opciju koju zelite." << endl;
	};
};

class NonExistentFile : public exception {
public:
	NonExistentFile(const char* msg) : exception(msg) {}

	void print()
	{
		cout << this->what() << "\nMolimo Vas da ponovo izaberete opciju koju zelite." << endl;
	};
};

class NonExistentStation : public exception {
public:
	NonExistentStation(const char* msg): exception(msg) {}

	void print()
	{
		cout << this->what() << "\nMolimo Vas da ponovo izaberete opciju koju zelite." << endl;
	};
};

class NonExistentLine : public exception {
public:
	NonExistentLine(const char* msg) : exception(msg) {}

	void print()
	{
		cout << this->what() << "\nMolimo Vas da ponovo izaberete opciju koju zelite." << endl;
	};
};

#endif // !EXCEPTION

