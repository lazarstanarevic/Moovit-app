#ifndef INTERFACE_H
#define INTERFACE_H

#include "BusNetwork.h"

class Interface {
public:
	Interface();
	~Interface();

	void work();

private:
	BusNetwork* BN;
	bool empty;

	void loadData();

	void stationInfo();
	void lineInfo();
	void lineStats();

	void getPath();
};

#endif // !INTERFACE

