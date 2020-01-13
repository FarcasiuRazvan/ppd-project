#pragma once
#include <string>
#include <vector>

using namespace std;


class schoolClass
{
public:
	string id;
	int nrHours;
	int nrSubjects;
	vector<pair<string, int>> subjects;
	vector<string> allSubjects;
	string timetable[6][8];
	vector<vector<string>> timetablesTable;
	schoolClass(string name, int hours, int subjectsNr);
	void addSubject(string id, int nrHours);
	void generateRandomTimetable();
	void initialiseTimtable();
	void generateAllTimetables();
	void allSubjectsVectorSetting();
private:
	void tipar(int p);
	int valid(int p);
	void bkt(int p);
	void cleanVectorTimetables();
	bool checkIfTimetableIsValid(vector<string> timeTable);

};

