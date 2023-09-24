#include "officehours.h"
#include <queue>
#include <set>
#include <map>
#include <ctime>
#include <cstdlib>
#include <fstream>

student::student(int timeArrivedIn){
	timeArrived = timeArrivedIn;
	static bool seededAlready = false;
    if (!seededAlready) {
        srand(time(0));
        seededAlready = true;
    }
    minsNeeded = (rand() % 10) + 1;
   	studID = (rand() % 60) + 1;
   	urgency = (rand() % 5) + 1;
   	string potentialTopics[15] = {"Ad Hoc Polymorphism", "Binary Trees", "Circular Arrays", "Datatypes", "Graphs", "Heaps", "Insertion Sort", "Maps", "Namespaces", "Priority Queues", "Queues", "Recursion", "Stacks", "Templatization", "Variables"};
   	topicOfVisit = potentialTopics[(rand() % 15)];
   	hasBeenAssisted = false;
}

bool newStudentArrived(){
	if(((rand()%7)+1) == 7){
		return true;
	}
	return false;
}

void multimapify_SSaTT(string storageFileName, multimap<size_t,pair<string,string> >& SSaTT){  // This text processing algorithm is completely proprietary to my custom 'student & topic' storage format
	ifstream storageFile(storageFileName);
	string currWord;
	string currStudID;
	string currStudSession;
	string currTopicOfVisit;
	bool studID_AlreadyRead = false;
	bool studSession_AlreadyRead = false;


	while(storageFile >> currWord){
		if(!studID_AlreadyRead && currWord[0] == '#'){
			size_t i=1;
			while(isdigit(currWord[i])){
				currStudID += currWord[i++];
			}
			studID_AlreadyRead = true;
		}
		
		else if(!studSession_AlreadyRead && currWord[0] == '#'){
			size_t i=1;
			while(currWord[i] != ':'){
				currStudSession += currWord[i++];
			}
			studSession_AlreadyRead = true;
		}
		
		if(studID_AlreadyRead && studSession_AlreadyRead && currWord[0] != '#'){
			if(currWord[0] == '|'){
				//cout << "Loading StudID: " << currStudID << " & session " << currStudSession << " & topic: " << currTopicOfVisit << endl; 
				SSaTT.emplace( stoi(currStudID), pair<string,string>(currStudSession,currTopicOfVisit) );
				currStudID.clear();
				currStudSession.clear();
				currTopicOfVisit.clear();
				studID_AlreadyRead = false;
				studSession_AlreadyRead = false;
			}
			else{
				currTopicOfVisit = currTopicOfVisit + currWord + " ";
			}
		}
	}
	storageFile.close();
}

void arrayify_SSaTT(string storageFileName, pair<size_t,pair<string,string> >*& SSaTT_array, size_t & len){
	ifstream storageFile(storageFileName);

	string currWord;
	string currStudID;
	string currStudSession;
	string currTopicOfVisit;
	bool studID_AlreadyRead = false;
	bool studSession_AlreadyRead = false;

	while(storageFile >> currWord){
		if(!studID_AlreadyRead && currWord[0] == '#'){
			size_t i=1;
			while(isdigit(currWord[i])){
				currStudID += currWord[i++];
			}
			studID_AlreadyRead = true;
		}
		
		else if(!studSession_AlreadyRead && currWord[0] == '#'){
			size_t i=1;
			while(currWord[i] != ':'){
				currStudSession += currWord[i++];
			}
			studSession_AlreadyRead = true;
		}
		
		if(studID_AlreadyRead && studSession_AlreadyRead && currWord[0] != '#'){
			if(currWord[0] == '|'){
				//cout << "Loading StudID: " << currStudID << " & session " << currStudSession << " & topic: " << currTopicOfVisit << endl; 

				pair<size_t,pair<string,string> >* temp_SSaTT_array = new pair<size_t,pair<string,string> >[++len];
				for(size_t i=0;i<len;++i){
					temp_SSaTT_array[i] = SSaTT_array[i];
				}

				temp_SSaTT_array[len-1] = make_pair(stoi(currStudID),make_pair(currStudSession,currTopicOfVisit));

				delete [] SSaTT_array;
				SSaTT_array = temp_SSaTT_array;

				currStudID.clear();
				currStudSession.clear();
				currTopicOfVisit.clear();
				studID_AlreadyRead = false;
				studSession_AlreadyRead = false;
			}
			else{
				currTopicOfVisit = currTopicOfVisit + currWord + " ";
			}
		}
	}
	storageFile.close();
}

void search_SSaTT(string storageFileName, bool searchStudents, string searchTerm){
	size_t len = 0;
	pair<size_t,pair<string,string> >* SSaTT_array = new pair<size_t,pair<string,string> >[len];
	arrayify_SSaTT(storageFileName,SSaTT_array,len);
	bool resultsFound = false;

	if(searchStudents){
		cout << "Printing information for student #" << searchTerm << "..." << endl;
		for(size_t i = 0; i < len; ++i){
			if(SSaTT_array[i].first == stoi(searchTerm)){
				resultsFound = true;
				if(SSaTT_array[i].second.first == "AH"){ cout << "> Attended after hours to ask about " << SSaTT_array[i].second.second << endl;}
				else{ cout << "> Attended session " << SSaTT_array[i].second.first << " to ask about " << SSaTT_array[i].second.second << endl; }
			}
		}
		if(!resultsFound){
			cout << "Sorry, no information found." << endl;
		}
		else{
			cout << "Search concluded." << endl;
		}
	}
	else{ // search by topic actually just searches for all topics in the SSaTT array with matching first characters.
		cout << "Printing students who asked about that topic..." << endl;
		for(size_t i = 0; i < len; ++i){
			if( (SSaTT_array[i].second.second)[0] == toupper(searchTerm[0]) || (SSaTT_array[i].second.second)[0] == searchTerm[0] ){
				resultsFound = true;
				if(SSaTT_array[i].second.first == "AH"){ cout << "> Student #" << SSaTT_array[i].first << " (after hours)." << endl; } // corrects syntax in case this student asked about the topic after-hours
				else{ cout << "> Student #" << SSaTT_array[i].first << " (during session " << SSaTT_array[i].second.first << ")." << endl; }
			}
		}
		if(!resultsFound){
			cout << "Sorry, no information found." << endl;
		}
		else{
			cout << "Search concluded." << endl;
		}
	}
	return;
}

void get_search_SSaTT_style(string storageFileName){
	char result;
	cout << "How would you like to search 'Student Sessions & Their Topics'?" << endl;
	cout << " -Type '1' to search by Student" << endl;
	cout << " -Type '2' to search by Topic" << endl; // The topic search feature actually just searches for all topics in the SSaTT array with a matching first character. This isn't problematic as I've deliberately made the first char of all topics alphabetically unique.
	do{
		cout << "Select '1' or '2': ";
		cin >> result;
	}
	while (!(result == '1' || result == '2'));

	cout << "----------------------------------------------------------------------" << endl;
	string result2;
	if(result == '1'){
		cout << "Provide a Student ID: ";
		cin >> result2;
		search_SSaTT("recent_SSaTT", 1, result2);
	}
	else{
		string potentialTopics[15] = {"Ad Hoc Polymorphism", "Binary Trees", "Circular Arrays", "Datatypes", "Graphs", "Heaps", "Insertion Sort", "Maps", "Namespaces", "Priority Queues", "Queues", "Recursion", "Stacks", "Templatization", "Variables"};
		for(size_t i = 0; i < 15; ++i){
			cout << "Type '" << (potentialTopics[i])[0] << "' to search for '" << potentialTopics[i] << "'." << endl;
		}
		cout << "----------------------------------------------------------------------" << endl;
		bool matchFound = false;
		while(!matchFound){
			cout << "Choose a letter from above: ";
			cin >> result2;
			for(size_t i = 0; i < 15; ++i){ //this verifies that the user doesn't enter a letter that no topics start with
				if(result2[0] == (potentialTopics[i])[0] || toupper(result2[0]) == (potentialTopics[i])[0]){ matchFound = true; break; }
			}
		}
		search_SSaTT("recent_SSaTT",0,result2);
	}
}

void sort_SSaTT(string storageFileName, bool isAscending, bool sortStudents){ 
	// Yes, I could've just used the multimap class' built-in sorting functionality, but instead had to 
	// demonstrate sorting manually for this assignment. Also, I'm aware that bubblesort becomes extremely
	// inefficient when isAscending == 0 && sortStudents == 1, as this case requires a full reverse
	// of the SSaTT array (because, by default, the multimap used to create the file stores the SSaTT in
	// isAscending == 1 && sortStudents == 1 format). This flaw should be fixed in later OHS implementations.

	size_t len = 0;
	pair<size_t,pair<string,string> >* SSaTT_array = new pair<size_t,pair<string,string> >[len];
	arrayify_SSaTT(storageFileName,SSaTT_array,len);


	cout << "Sorting... ";
	bool swapOccured;
	for(size_t i = 0; i < len - 1; ++i){
		swapOccured = false;
		for(size_t j = 0; j < len - i - 1; ++j){
			if( isAscending ? ( sortStudents ? SSaTT_array[j].second.second > SSaTT_array[j+1].second.second : SSaTT_array[j].first > SSaTT_array[j+1].first ) : ( sortStudents ? SSaTT_array[j].second.second < SSaTT_array[j+1].second.second : SSaTT_array[j].first < SSaTT_array[j+1].first )){
				//cout << "Swapping students " << SSaTT_array[j].first << " and " << SSaTT_array[j+1].first << "." << endl;
				swap(SSaTT_array[j],SSaTT_array[j+1]);
				swapOccured = true;
			}
		}
		if(swapOccured == false){ cout << "complete! Check the '" << storageFileName << "' file for results. " << endl; break; }
	}

	ofstream storageFile(storageFileName);

	for(size_t i=0;i<len;++i){
		//cout << "Writing to storage file: Student #" << SSaTT_array[i].first << ", Session #" << SSaTT_array[i].second.first << ": " << SSaTT_array[i].second.second << " |" << endl;
		storageFile << "Student #" << SSaTT_array[i].first << ", Session #" << SSaTT_array[i].second.first << ": " << SSaTT_array[i].second.second << " |" << endl;
	}
	
	storageFile.close();
}

void get_sort_SSaTT_style(string storageFileName){
	char result;
	cout << "How would you like 'Student Sessions & Their Topics' sorted?" << endl;
	cout << " -Type '1' for student ID, ascending" << endl; // the multimap sorts entries like this anyway!
	cout << " -Type '2' for student ID, descending" << endl;
	cout << " -Type '3' for topic asked, ascending" << endl;
	cout << " -Type '4' for topic asked, descending" << endl;
	do{
		cout << "Select 1-4: ";
		cin >> result;
	}
	while (!(result == '1' || result == '2' || result == '3' || result == '4'));

	if(result == '1'){
		sort_SSaTT(storageFileName,1,0);
	}
	else if(result == '2'){
		sort_SSaTT(storageFileName,0,0);
	}
	else if(result == '3'){
		sort_SSaTT(storageFileName,1,1);
	}
	else{
		sort_SSaTT(storageFileName,0,1);
	}
}

bool intelligible_main_menu_selection(string & result){
	// Modfies the string input 'result' such that it conforms to one of three main selection possibilities: 
	// 'search', 'sort', or 'quit', and returns true. If, however, the string input 'result' is unintelligible, 
	// then this function returns false (forcing the user to type another result in the main menu selection while loop).
	if(result == "search" || result == "sort" || result == "quit"){ return true; } //simplest scenario. the user typed their selection perfectly.
	else if(result == "Search" || result == "SEARCH"){ result = "search"; return true; }
	else if(result == "Sort" || result == "SORT"){ result = "sort"; return true; }
	else if(result == "Quit" || result == "QUIT" || ( (result[0] == 'q' || result[0] == 'Q') && (result.length() == 1) ) ){ result = "quit"; return true; }
	cout << "ERROR: could not interpret '" << result << "'" << endl;
	return false;
}

void OHS(size_t amtRuns){ //(Office Hours Simulation)
	StatLogger logStat;
	ofstream recent_SSaTT ("recent_SSaTT");
	recent_SSaTT.close();
	for(size_t currSessionNum = 1; currSessionNum <= amtRuns; currSessionNum++){
		cout << "----------------------------------------- SESSION " << currSessionNum << " STARTED! -----------------------------------------" << endl;
		priority_queue<student*, vector<student*>, compareStudentUrgencies> line;
		set<string> topicsAsked;
		multimap< size_t,pair<string,string> > SSaTT; //<---- "Students' Sessions and Their Topics"
		multimapify_SSaTT("recent_SSaTT",SSaTT);
		int minsRemaining = 60;
		student* currStudent = nullptr;
		while(minsRemaining > 0){

			cout << "| Minutes remaining: " << minsRemaining;
			if(!line.empty() || currStudent != nullptr){
				if(currStudent != nullptr){
					cout << " | Student in office: #" << currStudent->getStudID();
				}
				if(!line.empty()){
					cout << " | Others waiting: " << line.size() << " | Next in line: #" << line.top()->getStudID();
				}
				cout << " |" << endl;
			}
			else{
				cout << " | Professor unoccupied |" << endl;
			}

			if(newStudentArrived()){
				student *newStudent = new student(minsRemaining);
				cout << "New student #" << newStudent->getStudID() << " needs " << newStudent->getMinsNeeded() << " minutes of assistance at urgency level " << newStudent->getUrgency() << "." << endl; //Optional print line for diagnostics. Omit to optimize.
				logStat.TATN(newStudent->getMinsNeeded());
				logStat.TS(1); //<-- Increments 'totalStudents' variable by 1
				if(currStudent == nullptr){
					currStudent = newStudent; //if the line is empty, any new student can enter the office immediately
				}
				else{
					line.push(newStudent); // otherwise they've gotta wait in line
				}
			}
			
			if(currStudent != nullptr){ //as long as there's a student waiting
				if(currStudent->getMinsNeeded() > 1){ //if the current student still needs assistance
					currStudent->changeMinsNeeded(-1); //then spend a minute helping them
				}
				else{
					cout << "✓ Student #" << currStudent->getStudID() << " has been assisted. ✓" << endl; //Optional print line for diagnostics. Omit to optimize.
					logStat.TWT(currStudent->getTimeArrived() - minsRemaining);
					topicsAsked.insert(currStudent->getTopicOfVisit());
					SSaTT.emplace( currStudent->getStudID(), pair<string,string>(to_string(currSessionNum),currStudent->getTopicOfVisit()) );

					if(!line.empty()){
						delete currStudent;
						currStudent = line.top();
						line.pop();
					}
					else{
						delete currStudent;
						currStudent = nullptr;
					}
				}
			}
			minsRemaining--;
		}
		cout << "OFFICE HOURS HAS ENDED. PROFESSOR WILL ASSIST REMAINING STUDENTS." << endl;
		while(currStudent != nullptr){
			logStat.TO(1); //<-- Increments 'totalOvertime' variable by 1
			if(currStudent->getMinsNeeded() > 1){
				cout << "| Student in office: #" << currStudent->getStudID();
				if(!line.empty()){
					cout << " | Others waiting: " << line.size() << " | Next in line: #" << line.top()->getStudID() << " |" << endl;
				}
				else{
					cout << " |" << endl;
				}
				currStudent->changeMinsNeeded(-1);
			}
			else{
				cout << "✓  Student #" << currStudent->getStudID() << " has been assisted. ✓" << endl; //Optional print line for diagnostics. Omit to optimize.
				topicsAsked.insert(currStudent->getTopicOfVisit());
				SSaTT.emplace( currStudent->getStudID() ,pair<string,string>("AH",currStudent->getTopicOfVisit()) );
				if(!line.empty()){
					delete currStudent;
					currStudent = line.top();
					line.pop();
				}
				else{
					delete currStudent;
					currStudent = nullptr;
				}
			}
		}
		ofstream currSessionInfo ("OHS Session " + to_string(currSessionNum)); // <---- Creates a new file to fill with session information from set
		currSessionInfo << "All topics asked:" << endl;
		cout << endl;
		cout << "All topics asked: " << endl;
		for(set<string>::iterator  it = topicsAsked.begin(); it!=topicsAsked.end(); ++it){
			currSessionInfo << "•" << *it << endl;
			cout << "•" << *it << endl;
		}
		currSessionInfo.close();

		ofstream recent_SSaTT("recent_SSaTT");
		for(multimap< size_t,pair<string,string> >::iterator it = SSaTT.begin(); it!=SSaTT.end(); ++it){
			recent_SSaTT << "Student #" << it->first << ", Session #" << it->second.first << ": " << it->second.second << " |" << endl;
		}
		recent_SSaTT.close();
	}
	cout << "\n✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓ " << amtRuns << " sessions simulated successfully! ✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓" << endl;
	logStat.printAll(amtRuns);

	bool userWantsDataInteraction = true;

	while(userWantsDataInteraction){
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Would you like to 'search' or 'sort' all simulation data, or 'quit'?" << endl;
		string result;

		do{
			cout << "Type your selection: ";
			cin >> result;
		}
		while (!intelligible_main_menu_selection(result));
		if(result == "search"){
			cout << "----------------------------------------------------------------------" << endl;
			get_search_SSaTT_style("recent_SSaTT");
		}
		else if(result == "sort"){
			cout << "----------------------------------------------------------------------" << endl;
			get_sort_SSaTT_style("recent_SSaTT");
		}
		else{ //if the program reaches this condition then it must be certain that result == quit
			userWantsDataInteraction = false;
		}
	}
}
