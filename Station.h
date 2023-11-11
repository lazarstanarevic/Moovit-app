#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Station {
public:
	Station(const string& name, const int code,const int id);

	void printStationInfo();

	string getName() const;
	int getCode() const;
	int getId() const;
	vector<int> getLines();
	vector<string> getLinesNames();

	void addLine(int line);
	void addLineName(string name);
private:
	string name_;
	int code_;
	int id_;
	vector<int> lines_;
	vector<string> lines_names_;
};

#endif // !STATION_H