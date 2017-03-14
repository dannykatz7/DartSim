#include "Course.h"
#include "stdafx.h"

Course::Course() {
	
}

Course::Course(string nam, string loc, vector<DateAndTime> dts, Professor prof)
{
	professor = prof;
	set_event_name(nam);
	set_event_location(loc);
	set_event_times(dts);
}


Course::~Course()
{
}

Professor Course::getProf() {
	return professor;
}