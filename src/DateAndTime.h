#pragma once
#include<iostream>
#include<string>
using namespace std;

class Date {
	int year;
	int month;
	int day;

public:
	Date() : year(99999999), month(99999999), day(99999999) {
	}

	void setYear(int year)
	{
		this->year = year;
	}
	void setMonth(int month)
	{
		this->month = month;
	}
	void setDay(int day)
	{
		this->day = day;
	}
	int getYear()
	{
		return year;
	}
	int getMonth()
	{
		return month;
	}
	int getDay()
	{
		return day;
	}
	string getDate() {
		string a = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
		return a;
	}
};

class Time {
	int hours;
	int minutes;

public:
	void setHours(int hours)
	{
		this->hours = hours;
	}
	void setMinutes(int mins)
	{
		minutes = mins;
	}
	int getHours()
	{
		return hours;
	}
	int getMinutes()
	{
		return minutes;
	}
	string getTime() {
		string a = to_string(hours) + ":" + to_string(minutes);
		return a;
	}
	double getfloatingTime()
	{
		return hours + (minutes / 60.0);
	}
};
