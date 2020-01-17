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


	int NR_DAYS = 2;
	int MAX_NR_HOURS = 3;
	vector<pair<string, int>> subjects;
	vector<string> allSubjects;
	string timetable[6][8];
	int indexTimeTablesTable=1;
	vector<vector<string>> timetablesTable;
	schoolClass(string name, int hours, int subjectsNr);
	void addSubject(string id, int nrHours);
	void generateRandomTimetable();
	void initialiseTimtable();
	void generateAllTimetables();
	void allSubjectsVectorSetting();
	void setTimeTable();
private:
	void tipar(int p);
	int valid(int p);
	void bkt(int p);
	void cleanVectorTimetables();
	bool checkIfTimetableIsValid(vector<string> timeTable);

};

