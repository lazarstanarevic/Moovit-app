#include "Line.h"
#include <fstream>
#include <set>

Line::Line(int start, int end, int delta, const string& name, const int id, const vector<Station*>& stations)
:start_time(start), end_time(end), delta_time(delta), name_(name), id_(id), stations_(stations) 
{
    for (int i = 0;i < stations.size();i++) maps[stations[i]] = i;
}

Line::~Line()
{
}

void Line::printInfo()
{
    ofstream out("linija_" + name_ + ".txt");

    int end = stations_.size() - 1;

    out << name_ << " " << stations_[0]->getName() << "->" << stations_[end]->getName() << endl;

    for (int i = 0;i < stations_.size();i++)
    {
        out << stations_[i]->getCode() << " " << stations_[i]->getName();

        if (i != (stations_.size() - 1)) out << endl;
    }

    out.close();
}

void Line::printLineStats()
{
    set<string> names;
    vector<string> sol;

    for (int i = 0;i < stations_.size();i++)
    {
        vector<string> tmp= stations_[i]->getLinesNames();

        for (int j = 0;j < tmp.size();j++) names.insert(tmp[j]);
    }

    for (auto it = names.begin();it != names.end();it++)
    {
        if (*it != name_) sol.push_back(*it);
    }


    ofstream out("statistika_" + name_ + ".txt");

    out << name_ << endl;

    for (int i = 0;i < sol.size();i++)
    {
        out << sol[i];

        if (i == (sol.size() - 1)) out << endl;
        else out << " ";
    }

    out << getNumberOfDepartures();

    out.close();
}

vector<Station*> Line::getPath(Station* start, Station* end)
{
    vector<Station*> ret;

    int pos_s = maps[start], pos_e = maps[end];

    if (pos_s <= pos_e)
    {
        for (int i = pos_s;i <= pos_e;i++) ret.push_back(stations_[i]);
    }
    else
    {
        for (int i = pos_s;i >= pos_e;i--) ret.push_back(stations_[i]);;
    }

    return ret;
}

int Line::getNumberOfDepartures()
{
    int num = (end_time - start_time) / delta_time;

    if (((end_time - start_time) % delta_time) == 0) num++;

    return num;
}

int Line::getWaitingTime(int arrival_time, Station* station_s, Station* station_e)
{
    int waiting_time, bus_time, stations_num = stations_.size() - 1;
    
    int pos_s = maps[station_s], pos_e = maps[station_e];
    
    
    if (pos_s < pos_e) bus_time = start_time + pos_s * 3;

    else bus_time = start_time + (2 * stations_num - pos_s) * 3;
    //bus_time = start_time + (stations_num - pos_s) * 3;
    
    if (arrival_time > (bus_time - start_time + end_time)) return -1;

    if (arrival_time < bus_time) waiting_time = bus_time - arrival_time;
    
    else waiting_time = (delta_time - (arrival_time - bus_time) % delta_time) % delta_time;
 

    return waiting_time;
}

string Line::getName() const
{
    return name_;
}

int Line::getId() const
{
    return id_;
}

vector<Station*> Line::getStations() const
{
    return stations_;
}

int Line::getId(Station* stat)
{
    return maps[stat];
}