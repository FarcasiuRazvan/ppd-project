#include <iostream>
#include <fstream>
#include <sstream>
#include "schoolClass.h";
#include <vector>
#include <thread>

using namespace std;
fstream fin("input.in");
ofstream fout("output.out");
vector<pair<schoolClass,bool>> schoolClasses;
int nrClasses;

void readingInput() {
	string nr;
	getline(fin, nr);
	nrClasses = stoi(nr);
	int nrClass;
	int nrSameClass;
	int nrHours;
	int nrSubjects;
	for (int i = 0; i < nrClasses;i++)
	{
		string line;
		getline(fin,line);
		vector<string> tokens;

		stringstream check1(line);
		string aux;

		while (getline(check1, aux, ' ')) {
			tokens.push_back(aux);
		}
		nrClass = stoi(tokens[0]);
		nrSameClass = stoi(tokens[1]);
		nrHours= stoi(tokens[2]);
		nrSubjects= stoi(tokens[3]);

		vector<pair<string, int>> subjects;

		for (int x = 0; x < nrSubjects; x++)
		{
			string subjectLine;
			getline(fin, subjectLine);
			vector<string> subjectTokens;

			stringstream check2(subjectLine);
			string aux1;

			while (getline(check2, aux1, ' ')) {
				subjectTokens.push_back(aux1);
			}
			pair<string, int> p(subjectTokens[0], stoi(subjectTokens[1]));
			subjects.push_back(p);
		}
		for (int j = 0; j < nrSameClass; j++) {
			string id = to_string(nrClass);
			id.push_back(char('A'+j));
			schoolClass s(id, nrHours, nrSubjects);
			for (int x=0; x < nrSubjects; x++)
				s.addSubject(subjects[x].first, subjects[x].second);
			s.generateRandomTimetable();
			pair<schoolClass, bool> p1(s, false);
			schoolClasses.push_back(p1);
		}
	}
}

void printAfterRead() {
	for (int i = 0; i < schoolClasses.size(); i++) {
		cout << schoolClasses[i].first.id << " " << schoolClasses[i].second << endl;
		/*for (int j = 0; j < schoolClasses[i].first.subjects.size(); j++)
			cout << schoolClasses[i].first.subjects[j].first << " " << schoolClasses[i].first.subjects[j].second << endl;
		cout << endl << endl;*/
		cout << "Timetable" << endl;
		for (int j = 0; j < 5; j++)
		{
			for (int x = 0; x < 7; x++)
				cout << schoolClasses[i].first.timetable[j][x] << " ";
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}
}

bool verifyTimetablesCollisions(int secondIndex) {
	for (int firstIndex = 0; firstIndex < schoolClasses.size() && secondIndex!=firstIndex; firstIndex++) {
		if (schoolClasses[firstIndex].second == true)
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 8; j++)
				{
					if (schoolClasses[firstIndex].first.timetable[i][j] == schoolClasses[secondIndex].first.timetable[i][j] 
						&& schoolClasses[secondIndex].first.timetable[i][j] != "Break")
						return true;
				}
		}
	}
	schoolClasses[secondIndex].second = true;
	return false;
}

vector<int> verifyAll() {
	vector<int> indexes;
	for (int i = 0; i < schoolClasses.size(); i++)
		if (verifyTimetablesCollisions(i)) indexes.push_back(i);
	return indexes;
}

void permuteSchedule(int index) {
	int i = 0;
	int j = 0;
	vector<string> aux;
	for (int i = 0; i < 5; i++)
	{
		aux.push_back(schoolClasses[index].first.timetable[i][0]);
		for (int j = 0; j < 6; j++)
			if(schoolClasses[index].first.timetable[i][j+1]!="Break")
			schoolClasses[index].first.timetable[i][j] = schoolClasses[index].first.timetable[i][j + 1];
	}
	aux.push_back(aux[0]);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++)
			if (schoolClasses[index].first.timetable[i][j + 1] == "Break")
			{
				schoolClasses[index].first.timetable[i][j] = aux[i+1];
				break;
			}
}

void fixingSchedule(int index) {
	int cont = 0;
	//int cont2 = 0;
	cout << index << endl;
	while (verifyTimetablesCollisions(index)) {
		permuteSchedule(index);
		cont++;
		if (cont == schoolClasses[index].first.nrHours) {
			cont = 0;
			schoolClasses[index].first.generateRandomTimetable();
			//cont2++;
		}
		//if (cont2 == 4000) {
		//	srand(time(NULL));
		//	int randomIndex=rand() % schoolClasses.size();
		//	schoolClasses[randomIndex].first.generateRandomTimetable();
		//	break;
		//}
	}
}



void normal(int index) {
	int cont = 0;
	while (verifyTimetablesCollisions(index))
	{
		permuteSchedule(index);
		cont++;
		if (cont == schoolClasses[index].first.nrHours) { 
			cont = 0;
			cout <<endl<<"------------------------------"<< "KIND OF ERROR " << schoolClasses[index].first.id << endl;
			schoolClasses[index].first.generateRandomTimetable();
		}
	}
	cout << "True " << cont;
	//printAfterRead();
}

int main() {
	srand(time(NULL));
	readingInput();
	//printAfterRead();
	schoolClasses[0].first.generateAllTimetables();
	vector<vector<string>> timetables = schoolClasses[0].first.timetablesTable;
	for (int i = 0; i < timetables.size(); i++)
	{
		for (int j = 0; j < timetables[i].size(); j++)
			cout << timetables[i][j] << " ";
		cout << endl;
	}
	//vector<int> indexes = verifyAll();
	//while (indexes.size() > 0)
	//{
	//	int nrthreads = indexes.size();
	//	for (int i = 0; i < schoolClasses.size(); i++)
	//	{
	//		if (find(indexes.begin(), indexes.end(), i) == indexes.end())
	//			schoolClasses[i].second = true;
	//		else schoolClasses[i].second = false;
	//	}
	//	cout << endl << "INDEXES: ";
	//	for (int u = 0; u < indexes.size(); u++)
	//		cout << indexes[u] << " ";
	//	cout << endl;

	//	vector<thread> threads;
	//	for (int i = 0; i < nrthreads; i++)
	//		threads.push_back(thread(fixingSchedule, indexes[i]));

	//	for (int i = 0; i < threads.size(); i++)
	//		threads[i].join();
	//	indexes = verifyAll();
	//}
	///*for (int i = 1; i < schoolClasses.size(); i++)
	//	normal(i);

	//printAfterRead();*/
	//indexes = verifyAll();
	//for (int i = 0; i < indexes.size();i++) {
	//	cout << indexes[i];
	//}
	//printAfterRead();
	return 0;
}