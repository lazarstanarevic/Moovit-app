#include "BusNetwork.h"

#include <algorithm>
#include <fstream>
#include <limits>
#include <queue>
#include <set>
#define mp make_pair
#define station first
#define line second


BusNetwork::BusNetwork()
{	
}

BusNetwork::~BusNetwork()
{
	for (int i = 0;i < lines_.size();i++) delete lines_[i];

	for (int i = 0;i < stations_.size();i++) delete stations_[i];

	delete[] g_;  
	delete[] parent;
} 

void BusNetwork::loadStations(const string& filepath)
{
	ifstream in(filepath);

	if (in.fail()) throw new NonExistentFile("\nFajl sa datim imenom ne postoji.\n");

	string data;

	int id = 0, i = 0;

	while (getline(in,data))
	{
		for (i = 0;i < data.size();i++)
		{
			if (data[i] == ' ') break;
		}

		int code = stoi(data.substr(0, i));

		string name = data.substr(i + 1, data.size() - i - 1);

		Station* stat = new Station(name, code, id);

		map_stat[code] = stat;

		stations_.push_back(stat);

		id++;
	}

	this->initialize();

	in.close();
}

void BusNetwork::loadLines(const string& filepath)
{
	ifstream in(filepath);

	if (in.fail()) throw new NonExistentFile("\nFajl sa datim imenom ne postoji.\n");

	string data,name;
	vector<Station*> stations;
	int st = 0, et = 0, dt = 0, id = 0;

	while (getline(in, data))
	{

		stations.clear();

		parsLine(name, st, et, dt, stations, data);

		Line* line = new Line(st, et, dt, name, id, stations);

		map_line[name] = line;

		for (int i = 0;i < stations.size();i++)
		{
			stations[i]->addLine(id);

			stations[i]->addLineName(name);

			if (i == 0) continue;

			int u = stations[i]->getId(), v = stations[i - 1]->getId();

			g_[u].push_back(mp(v,line));

			g_[v].push_back(mp(u, line));
		}
		
		lines_.push_back(line);

		id++;
	}

	in.close();
}

void BusNetwork::printStationInfo(const string& code)
{
	if (!checkStation(code)) throw new NonExistentStation("\nNe postoji stanica sa datim kodom.\n");

	Station* station = map_stat[stoi(code)];

	station->printStationInfo();
}

void BusNetwork::printLineInfo(const string& name)
{
	if (!checkLine(name)) throw new NonExistentLine("\nNe postoji linija sa datim nazivom.\n");

	Line* line = map_line[name];

	line->printInfo();
}

void BusNetwork::printLineStats(const string& name)
{
	if (!checkLine(name)) throw new NonExistentLine("\nNe postoji linija sa datim nazivom.\n");

	Line* line = map_line[name];

	line->printLineStats();
}

void BusNetwork::printPathDijkstra(Station* start, Station* end)
{
	vector<pair<Station*, Line*>> path;

	Station* curr = end;
	path.push_back(mp(end, lines_[0]));

	while (dist[curr->getId()] != 0)
	{
		path.push_back(parent[curr->getId()][0]);

		curr = parent[curr->getId()][0].station;
	}

	reverse(path.begin(), path.end());


	ofstream out("putanja_" + to_string(start->getCode()) + "_" + to_string(end->getCode()) + ".txt");

    int i = 0;
	
	for (i = 0;i < path.size() - 1;i++)
	{
		if(i==0) out << "->" << path[i].line->getName() << endl;
		
		else if (path[i].line->getId() != path[i - 1].line->getId())
		{
			out << path[i].station->getCode() << endl;

			out << path[i - 1].line->getName() << "->" << path[i].line->getName() << endl;
		}

		out << path[i].station->getCode() << " ";
	}

	out << path[i].station->getCode();

	out.close();
}

void BusNetwork::printPathBfs(Station* start, Station* end)
{
	vector<pair<Station*, Line*>> path;

	Station* curr = end;
	path.push_back(mp(end, lines_[0]));

	while (dist[curr->getId()] != 0)
	{
		path.push_back(parent[curr->getId()][0]);

		curr = parent[curr->getId()][0].station;
	}
	
	reverse(path.begin(), path.end());


	ofstream out("putanja_" + to_string(start->getCode()) + "_" + to_string(end->getCode()) + ".txt");

	for (int i = 0;i < path.size() - 1;i++)
	{	
		if (i == 0) out << "->" << path[i].line->getName() << endl;
		else out << path[i - 1].line->getName() << "->" << path[i].line->getName() << endl;


		vector<Station*> tmp = path[i].line->getPath(path[i].station, path[i + 1].station);

		for (int i = 0;i < tmp.size();i++)
		{
			if (i != 0) out << " ";

			out << tmp[i]->getCode();
		}
		
		if (i != (path.size() - 2)) out << endl;
	}

	out.close();
}

void BusNetwork::dijkstra(const string& start_s, const string& end_s, const string& time)
{
	prepare();

	int start_time = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));

	if(!(checkStation(start_s) && checkStation(end_s))) throw new NonExistentStation("\nStanice sa datim kodom ne postoje.\n");

	Station* start = map_stat[stoi(start_s)];
	Station* end = map_stat[stoi(end_s)];

	priority_queue <pair<int, int>> pq;

	int start_station = start->getId();

	pq.push(mp(0, start_station));

	dist[start_station] = 0;

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		//visited_[u] = true;

		for (auto tmp : g_[u])
		{
			int v = tmp.first;
			Line* curr_line = tmp.second;

			//if (visited_[v] == true) continue;

			int wt = curr_line->getWaitingTime(start_time + dist[u], stations_[u], stations_[v]);

			if (wt == -1) continue;

			int cost = dist[u] + wt + 3;

			if (cost < dist[v])
			{
				dist[v] = cost;

				pq.push(mp(-1 * cost, v));

				parent[v].push_back(mp(stations_[u], curr_line));
			}
		}
	}

	//for (int i = 0;i < stations_.size();i++) cout << stations_[i]->getCode() << " " << dist[stations_[i]->getId()] << endl;

	printPathDijkstra(start, end);
}

void BusNetwork::bfs(const string& start, const string& end)
{
	if (!(checkStation(start) && checkStation(end))) throw new NonExistentStation("\nStanice sa datim kodom ne postoje.\n");

	Station* start_station = map_stat[stoi(start)];
	Station* end_station = map_stat[stoi(end)];

	prepare();

	queue<Station*> q;

	q.push(start_station);

	dist[start_station->getId()] = 0;

	visited_stations[start_station->getId()] = true;

	while (!q.empty())
	{
		Station* stat = q.front();
		q.pop();

		vector<int> curr_lines_ids = stat->getLines();

		for (int i = 0;i < curr_lines_ids.size();i++)
		{
			int line_id = curr_lines_ids[i];

			if (visited_lines[line_id] == true) continue;

			visited_lines[line_id] = true;

			vector<Station*> curr_stations = lines_[line_id]->getStations();

			for (int j = 0;j < curr_stations.size();j++)
			{
				int id = curr_stations[j]->getId();

				if (visited_stations[id] == true) continue;

				q.push(curr_stations[j]);

				dist[id] = dist[stat->getId()] + 1;

				parent[id].push_back(mp(stat, lines_[line_id]));

				visited_stations[id] = true;
			}
		}
	}

	printPathBfs(start_station, end_station);
}

void BusNetwork::parsLine(string& name, int& st, int& et, int& dt, vector<Station*>& stations, string& data)
{
	vector<string> elements;
	string tmp = "";

	for (int i = 0;i < data.size();i++)
	{	
		if (data[i] == ' ' || i == (data.size() - 1))
		{
			if (i == (data.size() - 1)) tmp += data[i];

			elements.push_back(tmp);
			tmp = "";
		}
		else tmp += data[i];
	}
	
	name = elements[0];

	for (int i = 2;i < elements.size();i++) stations.push_back(map_stat[stoi(elements[i])]);

	tmp = elements[1];

	st = stoi(tmp.substr(1, 2)) * 60 + stoi(tmp.substr(4, 2));

	et = stoi(tmp.substr(7, 2)) * 60 + stoi(tmp.substr(10, 2));

	dt = stoi(tmp.substr(13, tmp.size() - 14));
}

void BusNetwork::initialize()
{
	for (int i = 0;i < stations_.size();i++)
	{
		visited_lines.push_back(false);

		visited_stations.push_back(false); 

		dist.push_back(INT_MAX);
	}

	parent = new vector<pair<Station*, Line*>>[stations_.size()];
	
	g_ = new vector<pair<int, Line*>>[stations_.size()];
}

void BusNetwork::prepare()
{
	for (int i = 0;i < stations_.size();i++)
	{
		visited_stations[i] = false;

		visited_lines[i] = false;

		dist[i] = INT_MAX;

		parent[i].clear();
	}
}

bool BusNetwork::checkStation(string code)
{
	return map_stat.count(stoi(code));
}

bool BusNetwork::checkLine(string line_name)
{
	return map_line.count(line_name);
}