// DartSim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

Person parse_names(string);
Event build(string, vector<Person>&);

int main()
{	
	int catcher;
	vector<Person> people;
	vector<Event> events;
	string istring, estring;
	ifstream mynames, myevents;

	//Open the file with basic person info
	mynames.open("Text.txt");
	if (!mynames.is_open()) {
		cout << "Error finding read-in file: Text.txt, exiting program " << endl;
		exit(0);
	}

	//read the strings into proper forms and store in a vector of people
	while (getline(mynames, istring)) {
		people.insert(people.end(), parse_names(istring));
	}

	for (auto p : people)
		cout << p << endl;

	//Open the file with event info and people enrolled in given events
	myevents.open("Events.txt");
	if (!myevents.is_open()) {
		cout << "Error finding read-in file: Events.txt, exiting program " << endl;
		exit(0);
	}

	//read the strings into proper form and connect people to events
	while (getline(myevents, estring, ';')) {
		events.insert(events.end(), build(estring, people));
		for (auto p : people)
			cout << p << endl;
	}


	
	bool running = true;
	MasterClock clock;
	while (running) { //MAIN PROGRAM
		cout << "The time is " << clock.getHour() << "h" << " on day " <<
			clock.getDay() << endl;
		cout << "Press enter to advance 1 hour" << endl;
		cout << "Enter a number to advance that many hours" << endl;
		cout << "Enter \"next\" to advance a day" << endl;
		string input;
		getline(cin, input); 
		if (input == "")
			clock.tick();
		else if (input == "next" || input == "\"next\"")
			clock.nextDay();
		else if(atoi(input.c_str()) > 0)
			clock.tickHours(atoi(input.c_str()));
		else {}

		for (Person p : people) {
			p.onClock(clock);
			p.toString();
		}
		cout << endl;


	}
	cout << people.front() << endl;
	cin >> catcher;

	return 0;
}

Person parse_names(string istring) {
	const char c = ',';
	string buff{ "" };
	vector<string> v;
	Student stud;

	for (auto n : istring)
	{
		if (n != c) {
			buff += n;
		}
		else if (n == c && buff != "") {
			v.push_back(buff); 
			buff = ""; 
		}
	}
	if (buff != "") {
		v.push_back(buff);
	}

	if (v[0] == "s") {
		Student stud(v[1], v[2], stoi(v[3], nullptr, 10), stoi(v[4], nullptr, 10),
			stoi(v[5], nullptr, 10), stoi(v[6], nullptr, 10));
		return stud;
	}
	else if (v[0] == "p") {
		Professor prof(v[1], v[2], stoi(v[3], nullptr, 10), stoi(v[4], nullptr, 10),
			stoi(v[5], nullptr, 10), v[6]);
		return prof;
	}
	else {
		Person indiv(v[1], v[2], stoi(v[3], nullptr, 10), stoi(v[4], nullptr, 10),
			stoi(v[5], nullptr, 10));
		return indiv;
	}
}

Event build(string estring, vector<Person>& peeps) {
	int day_num;
	const char c = ',';
	string buff{ "" };
	vector<string> v;
	vector<DateAndTime> dts;

	for (auto n : estring)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	day_num = stoi(v[3], nullptr, 10);
	int i = 0;
	while (day_num > 0) {
		DateAndTime dt(stoi(v[4+i],nullptr,10),stoi(v[5+i],nullptr,10));
		dts.insert(dts.end(), dt);
		i += 2;
		--day_num;
	}
	
	if (v[0] == "e") {
		Event vent(v[1], v[2], dts);
		for (int i = 0; i < peeps.size(); ++i) {
			for (auto s : v) {
				if (s == peeps[i].getName()) 
					peeps[i].addEvent(vent);
			}
		}
		return vent;
	}
	else if (v[0] == "c") {
		Course crse(v[1], v[2], dts,  "need professor here"); //TODO: Add professor from csv here
	}
	else if (v[0] == "g") {

	}
	else {

	}
}