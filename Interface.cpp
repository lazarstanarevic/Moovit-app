#include "Interface.h"

Interface::Interface()
{
	BN = new BusNetwork();
	empty = true;

	cout << "Dobrodosli u simulator mreze gradskog prevoza.Molimo Vas, odaberite opciju :" << endl;
	cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl;
	cout << "0. Kraj rada" << endl;
}

Interface::~Interface()
{
	delete BN;
}

void Interface::work()
{
	int x;
	string code, line_name;
	bool ok = true;

	while (ok)
	{
		cin >> x;

		try 
		{
			if (empty && x != 1 && x != 0) throw new IndexOutOfRange("\nUneta opcija ne postoji.\n");

			switch (x)
			{
			case 0:
				ok = false;
				break;

			case 1:
				if (empty) this->loadData();
				else this->stationInfo();
				break;

			case 2:
				this->lineInfo();
				break;

			case 3:
				this->lineStats();
				break;

			case 4:
				this->getPath();
				break;

			default:
				throw new IndexOutOfRange("\nUneta opcija ne postoji.\n");
				break;
			}
		}
		catch (IndexOutOfRange* e)
		{
			e->print();
			delete e;
		}
		catch (NonExistentFile* e)
		{
			e->print();
			delete e;
		}
		catch (NonExistentStation* e)
		{
			e->print();
			delete e;
		}
		catch (NonExistentLine* e)
		{
			e->print();
			delete e;
		}
	}
}

void Interface::loadData()
{
	string file_name;

	cout << endl;
	cout << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl;
	cin >> file_name;
	BN->loadStations(file_name);

	cout << endl;
	cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" << endl;
	cin >> file_name;
	BN->loadLines(file_name);

	cout << endl;
	cout << "Mreza gradskog prevoza je uspesno ucitana.Molimo Vas, odaberite opciju :" << endl;
	cout << "1. Prikaz informacija o stajalistu" << endl;
	cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
	cout << "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl;
	cout << "4. Pronalazak putanje izmedju dva stajalista" << endl;
	cout << "0. Kraj rada" << endl;

	empty = false;
}

void Interface::stationInfo()
{ 
	string code;

	cout << endl;
	cout << "Molimo Vas, unesite sifru stajalista cije osnovne informacije zelite da prikazete." << endl;
	cin >> code;

	BN->printStationInfo(code);

	cout << endl;
	cout << "Generisan je fajl stajaliste_" << code << ".txt sa osnovnim informacijama o stajalistu " << code << endl;
}

void Interface::lineInfo()
{
	string line_name;

	cout << endl;
	cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
	cin >> line_name;

	BN->printLineInfo(line_name);

	cout << endl;
	cout << "Generisan je fajl linija_" << line_name << ".txt sa osnovnim informacijama o liniji " << line_name << endl;
}

void Interface::lineStats()
{
	string line_name;

	cout << endl;
	cout << "Molimo Vas, unesite oznaku linije ciju statistiku zelite da prikazete." << endl;
	cin >> line_name;

	BN->printLineStats(line_name);

	cout << endl;
	cout << "Generisan je fajl statistika_" << line_name << ".txt sa statistikom linije " << line_name << endl;
}

void Interface::getPath()
{
	int strat;
	string start, end, arrival_time;
	
	cout << endl;
	cout << "Molimo Vas, unesite kodove pocetne i krajnje stanice" << endl;
	cin >> start >> end;

	cout << endl;
	cout << "Molimo Vas, odaberite strategiju koju zelite da koristite za putovanje:" << endl;
	cout << "1. Nasumicna putanja" << endl;
	cout << "2. Putanja za koju je vreme putovanja najmanje" << endl;
	cout << "3. Putanja sa najmanje presedanja" << endl;

	cin >> strat;

	if (strat != 2) BN->bfs(start, end);
	else 
	{
		cout << "\nMolimo Vas, unesite vreme dolaska na pocetnu stanicu u formatu hh:mm" << endl;
		cin >> arrival_time;

		BN->dijkstra(start, end, arrival_time);
	}

	cout << endl;
	cout << "Generalisan je fajl putanja_" << start << "_" << end << ".txt koji sadrzi trazenu putanju" << endl;
}