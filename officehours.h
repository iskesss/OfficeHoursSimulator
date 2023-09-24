#ifndef OFFICEHOURS_H
#define OFFICEHOURS_H
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

class student {
public:
	student(int timeArrivedIn);

	size_t getMinsNeeded() const { return minsNeeded; }
	size_t getStudID() const { return studID; }
	size_t getUrgency() const { return urgency; }
	int getTimeArrived() const { return timeArrived; }
	string getTopicOfVisit() const { return topicOfVisit; }

	void changeMinsNeeded(int num) { minsNeeded = minsNeeded + num; }
private:
	string topicOfVisit;
	bool hasBeenAssisted;
	size_t minsNeeded;
	size_t studID;
	size_t urgency;
	int timeArrived;
};

struct compareStudentUrgencies{
	bool operator()(const student* lhs, const student* rhs){
		return lhs->getUrgency() < rhs->getUrgency();
	}
};

struct AlphabetizeTopics{
	bool operator ()(const string& lhs, const string& rhs){
		return lhs[0] < rhs[0];
	}
};

struct StatLogger{
	StatLogger(){
		totalStudents = new int(0);
		totalAssitanceTimeNeeded = new int(0);
		totalWaitTime = new int(0);
		totalOvertime = new int(0);
	}

	void TS(int input){	*totalStudents += input; }
	void TATN(int input) { *totalAssitanceTimeNeeded += input; }
	void TWT(int input){ *totalWaitTime += input; }
	void TO(int input){ *totalOvertime += input; }

	void printAll(size_t amtRuns){ //<--- given a specified amount of OHS sessions
		cout << endl;
		cout << "____________________PRINTING ALL SESSION STATISTICS___________________" << endl;
		cout << "><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><" << endl;
  		cout << "Total students attended (across " << amtRuns << " sessions): " << (*totalStudents) << endl;
  		cout << "Total mins students spent in queue: " << (*totalWaitTime) << endl;
  		cout << "><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><" << endl;
  		cout << "Avg mins spent waiting: " << double(*totalWaitTime)/(*totalStudents) << endl;
  		cout << "Avg mins spent with prof: " << double(*totalAssitanceTimeNeeded)/(*totalStudents) << endl;
  		cout << "Avg mins overtime: " << double((*totalOvertime))/amtRuns << endl;
  		cout << "><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><" << endl;
	}
	private:
		int *totalStudents;
		int *totalAssitanceTimeNeeded;
		int *totalWaitTime;
		int *totalOvertime;
};


bool newStudentArrived();

void multimapify_SSaTT(string storageFileName, multimap< size_t,pair<string,string> >& SSaTT);
void arrayify_SSaTT(string storageFileName, pair< size_t,pair<string,string> >*& SSaTT_array, size_t & len);

void sort_SSaTT(string storageFileName, bool isAscending, bool sortStudents);
void get_sort_SSaTT_style(string storageFileName);

void search_SSaTT(string storageFileName, bool searchStudents, string searchTerm);
void get_search_SSaTT_style(string storageFileName);

bool intelligible_main_menu_selection(string & result);
void OHS(size_t amtRuns);

#endif // NODE_H
 