#include <iostream>
#include <fstream>
#include <sstream>
#include "schoolClass.h";
#include <vector>
#include <thread>
#include <algorithm>

using namespace std;


schoolClass::schoolClass(string name, int hours, int subjectsNr)
{
	this->id = name;
	this->nrHours = hours;
	this->nrSubjects = subjectsNr;
}

void schoolClass::addSubject(string id, int nrHours)
{
	pair<string, int> p;
	p.first = id;
	p.second = nrHours;
	this->subjects.push_back(p);
}

void schoolClass::generateRandomTimetable()
{
	srand(time(NULL));
	this->initialiseTimtable();
	vector<int> nrHoursSubjects;
	for (int i = 0; i < this->nrSubjects; i++)
		nrHoursSubjects.push_back(this->subjects[i].second);
	int i = 0;
	int hour = 0;
	//cout << "----------------------------------" << endl;
	while(i<nrHours)
	{
		int subjectNr = rand() % this->nrSubjects;
		int day = rand() % 5;
		//cout <<day<<" "<<hour<<" "<< timetable[day][hour] << " " << this->subjects[subjectNr].second <<endl;
		if (timetable[day][hour] == "Break" && this->subjects[subjectNr].second>0)
		{
			//cout << hour;
			timetable[day][hour] = this->subjects[subjectNr].first;
			this->subjects[subjectNr].second--;
			i++;
			if (i % 5 == 0) hour += 1;
		}
	}
	//cout << endl;
	for (int i = 0; i < this->subjects.size(); i++)
	{
		if (this->subjects[i].second != 0) cout << "PROBLEM" << endl;
	}
	//cout << "----------------------------------" << endl;
	for (int i = 0; i < this->nrSubjects; i++)
		this->subjects[i].second=nrHoursSubjects[i];
}

void schoolClass::initialiseTimtable()
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 8; j++)
			this->timetable[i][j] = "Break";
}

void schoolClass::generateAllTimetables() {
	allSubjectsVectorSetting();
	bkt(0);
	cout << timetablesTable.size()<<endl;
	for (int i = 0; i < timetablesTable.size(); i++)
	{
		for (int j = 0; j < timetablesTable[i].size(); j++)
			cout << timetablesTable[i][j] << "|";
		cout << endl;
	}
	cleanVectorTimetables();
}

void schoolClass::allSubjectsVectorSetting()
{
	int breakHours=0;
	for (int i = 0; i < subjects.size(); i++)
		for (int j = 0; j < subjects[i].second; j++)
			allSubjects.push_back(subjects[i].first);
	//if (nrHours < 20) breakHours = 20 - nrHours;
	//else breakHours = 0;
	//for (int i = 0; i < breakHours; i++)
	//	allSubjects.push_back(" ");
}

void schoolClass::tipar(int p)
{
	int j;
	vector<string> newTimeTable;
	timetablesTable.push_back(newTimeTable);
	for (j = 0; j < p; j++)
		 timetablesTable[timetablesTable.size()-1].push_back(allSubjects[j]);
}

int schoolClass::valid(int p)
{
	int i, ok;
	ok = 1;
	for (i = 0; i < p-1; i++)
		if (allSubjects[p] == allSubjects[i])
			ok = 0;
	return ok;
}

void schoolClass::bkt(int p)
{
	int val;
	for (val = 0; val <= allSubjects.size(); val++)
	{
		if (valid(p))
			if (p==allSubjects.size())
				tipar(p);
			else
				bkt(p + 1);
	}
}

void schoolClass::cleanVectorTimetables()
{
	int i = 0;
	int dim = timetablesTable.size();
	while (i < dim){
		if (timetablesTable[i].size() < 35) { 
			timetablesTable.erase(timetablesTable.begin() + i); 
			dim--; 
			i--; 
		}
		i++;
	}
	while (i < dim) {
		if (checkIfTimetableIsValid(timetablesTable[i])==false) {
			timetablesTable.erase(timetablesTable.begin() + i);
			dim--;
			i--;
		}
		i++;
	}
}

bool schoolClass::checkIfTimetableIsValid(vector<string> timeTable)
{
	for (int i = 0; i < timeTable.size(); i += 7)
	{
		bool breakBool=true;
		int cont = 0;
		for (int j = i; j < i + 7; j++)
		{
			if (timeTable[j] == " " and breakBool == true) breakBool = false;
			if (timeTable[j] != " " and breakBool == false) return false;
			if (breakBool) cont++;
		}
		if (cont < 4) return false;
	}
	return true;

}

