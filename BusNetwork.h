#ifndef BUSNETWORK_H
#define BUSNETWORK_H

#include "Exception.h"
#include "Line.h"
#include "Station.h"
#include <map>

using namespace std;

class BusNetwork {
public:
	BusNetwork();
	~BusNetwork();

	void loadStations(const string& filepath);
	void loadLines(const string& filepath);

	void printStationInfo(const string& code);
	void printLineInfo(const string& name);
	void printLineStats(const string& name);

	void dijkstra(const string& start, const string& end, const string& time);
	void bfs(const string& start, const string& end);

private:
	vector<pair<int, Line*>>* g_;
	vector<Line*> lines_;
	vector<Station*> stations_;
	
	vector<bool> visited_stations;  
	vector<bool> visited_lines;
	vector<int> dist;
	vector<pair<Station*, Line*>>* parent;

	map<int, Station*> map_stat;
	map<string, Line*> map_line;

	void printPathDijkstra(Station* start, Station* end);
	void printPathBfs(Station* start, Station* end);

	void parsLine(string& name, int& st, int& et, int& dt, vector<Station*>& stations, string& data);
	void initialize();
	void prepare();

	bool checkStation(string code);
	bool checkLine(string line_name);
};

#endif // !BUSNETWORK