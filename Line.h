#ifndef LINE_H
#define LINE_H

#include "Station.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;


class Line {
public:
	Line(int start, int end, int delta, const string& name, const int id, const vector<Station*>& stations);
	~Line();

	int getWaitingTime(const int arrival_time, Station* station_s, Station* station_e);

	void printInfo();
	void printLineStats();

	vector<Station*> getPath(Station* start, Station* end);
	int getNumberOfDepartures();

	string getName() const;
	int getId() const;
	vector<Station*> getStations() const;
	int getId(Station* stat);
private:
	map <Station*, int> maps;
	int start_time;
	int end_time;
	int delta_time;
	string name_;
	int id_;
	vector<Station*> stations_;
};

#endif // !LINE_H