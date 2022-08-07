#pragma once
#include <iostream>
#include "DateAndTime.h"
using namespace std;

class Flight
{
	string Name_of_airline;
	double TicketPrice;
	Date date;
	Time FlyingTime;
	Time LandingTime;

public:
	Flight() :TicketPrice(99999999) {
	}

	void set_Name_of_airline(string airline)
	{
		Name_of_airline = airline;
	}

	void setTicketPrice(double TicketPrice)
	{
		this->TicketPrice = TicketPrice;
	}

	Date& getDate() {
		return date;
	}

	Time& getFlyingTime() {
		return FlyingTime;
	}

	Time& getLandingTime() {
		return LandingTime;
	}

	void setDate(int y, int m, int d)
	{
		date.setYear(y);
		date.setMonth(m);
		date.setDay(d);
	}

	void setFlyingTime(int h, int m)
	{
		FlyingTime.setHours(h);
		FlyingTime.setMinutes(m);
	}

	void setLandingTime(int h, int m)
	{
		LandingTime.setHours(h);
		LandingTime.setMinutes(m);
	}

	string get_Name_of_Airline()
	{
		return Name_of_airline;
	}

	double getTicketPrice()
	{
		return TicketPrice;
	}

	int getDay_of_Flight()
	{
		return date.getDay();
	}

	int getMonth_of_Flight()
	{
		return date.getMonth();
	}

	int getYear_of_Flight()
	{
		return date.getYear();
	}

	int getFlyingTime_Hour()
	{
		return FlyingTime.getHours();
	}

	int getFlyingTime_Minutes()
	{
		return FlyingTime.getMinutes();
	}

	int get_Total_Air_Time()
	{
		int count = 0;
		int flhour = FlyingTime.getHours();
		int ldhour = LandingTime.getHours();
		while (flhour != ldhour) {
			flhour++;
			count++;
			if (flhour == 24) {
				flhour = 0;
			}
		}

		return count;
	}
	Time get_Total_Air_Time_object()
	{
		Time Total_Air_Time;
		Total_Air_Time.setHours(abs(LandingTime.getHours() - FlyingTime.getHours()));
		Total_Air_Time.setMinutes(abs(LandingTime.getMinutes() - FlyingTime.getMinutes()));
		return Total_Air_Time;
	}
	double getTotalFlightTime()
	{
		return get_Total_Air_Time_object().getfloatingTime();
	}
	int getLandingTime_Hour()
	{
		return LandingTime.getHours();
	}
	int getLandingTime_Minutes()
	{
		return LandingTime.getMinutes();
	}
	string getDate_string() {
		return date.getDate();
	}
	string getLandingTime_string() {
		return LandingTime.getTime();
	}
	string getFlyingTime_string() {
		return FlyingTime.getTime();
	}
};

ostream& operator<<(ostream& output, Flight& obj) {
	cout << "		\tFlight Information:" << endl;
	cout << "			\t\t\tAirLine:  " << obj.get_Name_of_Airline() << endl;
	cout << "			\t\t\tTicket Price:  " << obj.getTicketPrice() << endl;
	cout << "			\t\t\tDate:  " << obj.getDay_of_Flight() << "/" << obj.getMonth_of_Flight() << "/" << obj.getYear_of_Flight() << endl;
	bool flhour, flmin, ldhour, ldmin;
	if (obj.getFlyingTime_Hour() < 10) {
		flhour = true;
	}
	else flhour = false;
	if (obj.getFlyingTime_Minutes() < 10) {
		flmin = true;
	}
	else flmin = false;
	if (obj.getLandingTime_Hour() < 10) {
		ldhour = true;
	}
	else ldhour = false;
	if (obj.getLandingTime_Minutes() < 10) {
		ldmin = true;
	}
	else ldmin = false;
	if (flhour == true && flmin == true) {
		cout << "			\t\t\tFlying Time:  0" << obj.getFlyingTime_Hour() << ":0" << obj.getFlyingTime_Minutes();
	}
	else if (flhour == true) {
		cout << "			\t\t\tFlying Time:  0" << obj.getFlyingTime_Hour() << ":" << obj.getFlyingTime_Minutes();

	}
	else if (flmin == true) {
		cout << "			\t\t\tFlying Time:  " << obj.getFlyingTime_Hour() << ":0" << obj.getFlyingTime_Minutes();

	}
	else cout << "			\t\t\tFlying Time:  " << obj.getFlyingTime_Hour() << ":" << obj.getFlyingTime_Minutes();
	cout << endl;
	//landing time
	if (ldhour == true && ldmin == true) {
		cout << "			\t\t\tLanding Time:  0" << obj.getLandingTime_Hour() << ":0" << obj.getLandingTime_Minutes();
	}
	else if (ldhour == true) {
		cout << "			\t\t\tLanding Time:  0" << obj.getLandingTime_Hour() << ":" << obj.getLandingTime_Minutes();

	}
	else if (ldmin == true) {
		cout << "			\t\t\tLanding Time:  " << obj.getLandingTime_Hour() << ":0" << obj.getLandingTime_Minutes();

	}
	else cout << "			\t\t\tLanding Time:  " << obj.getLandingTime_Hour() << ":" << obj.getLandingTime_Minutes();
	cout << endl;
	//duration time
	cout << "			\t\t\tDuration Time:  " << obj.get_Total_Air_Time() << " hour(s) ";
	cout << endl << endl;
	return output;
}