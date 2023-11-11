#include "Station.h"
#include <fstream>

Station::Station(const string& name, const int code, const int id) : name_(name), code_(code), id_(id) {}

void Station::printStationInfo()
{
	ofstream out("stajaliste_" + to_string(code_) + ".txt");

	out << code_ << " " << name_ << " [";

	for (int i = 0;i < lines_names_.size();i++)
	{
		if (i != 0) out << " ";

		out << lines_names_[i];
	}

	out << "]";

	out.close();
}

string Station::getName() const
{
	return name_;
}

int Station::getCode() const
{
	return code_;
}

int Station::getId() const
{
	return id_;
}

vector<int> Station::getLines()
{
	return lines_;
}

vector<string> Station::getLinesNames()
{
	return lines_names_;
}

void Station::addLine(int line)
{
	lines_.push_back(line);
}

void Station::addLineName(string name)
{
	lines_names_.push_back(name);
}
