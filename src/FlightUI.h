#pragma once
#include "Flight.h"

class FlightUI {
public:
	void displayFlights(string& src, string& desti, Flight& f) {
		cout << "\t-----------------------------------------------------------------------------------------------" << endl;
		cout << "\tSource:  " << src;
		cout << "						";
		cout << "\tDestination:  " << desti << endl;
		cout << "\t-----------------------------------------------------------------------------------------------" << endl;

		cout << "		\tFlight Information:" << endl;
		cout << "			\t\t\tAirLine:  " << f.get_Name_of_Airline() << endl;
		cout << "			\t\t\tTicket Price:  " << f.getTicketPrice() << endl;
		cout << "			\t\t\tDate:  " << f.getDay_of_Flight() << "/" << f.getMonth_of_Flight() << "/" << f.getYear_of_Flight() << endl;
		bool flhour, flmin, ldhour, ldmin;
		if (f.getFlyingTime_Hour() < 10) {
			flhour = true;
		}
		else flhour = false;
		if (f.getFlyingTime_Minutes() < 10) {
			flmin = true;
		}
		else flmin = false;
		if (f.getLandingTime_Hour() < 10) {
			ldhour = true;
		}
		else ldhour = false;
		if (f.getLandingTime_Minutes() < 10) {
			ldmin = true;
		}
		else ldmin = false;
		if (flhour == true && flmin == true) {
			cout << "			\t\t\tFlying Time:  0" << f.getFlyingTime_Hour() << ":0" << f.getFlyingTime_Minutes();
		}
		else if (flhour == true) {
			cout << "			\t\t\tFlying Time:  0" << f.getFlyingTime_Hour() << ":" << f.getFlyingTime_Minutes();

		}
		else if (flmin == true) {
			cout << "			\t\t\tFlying Time:  " << f.getFlyingTime_Hour() << ":0" << f.getFlyingTime_Minutes();

		}
		else cout << "			\t\t\tFlying Time:  " << f.getFlyingTime_Hour() << ":" << f.getFlyingTime_Minutes();
		cout << endl;
		//landing time
		if (ldhour == true && ldmin == true) {
			cout << "			\t\t\tLanding Time:  0" << f.getLandingTime_Hour() << ":0" << f.getLandingTime_Minutes();
		}
		else if (ldhour == true) {
			cout << "			\t\t\tLanding Time:  0" << f.getLandingTime_Hour() << ":" << f.getLandingTime_Minutes();

		}
		else if (ldmin == true) {
			cout << "			\t\t\tLanding Time:  " << f.getLandingTime_Hour() << ":0" << f.getLandingTime_Minutes();

		}
		else cout << "			\t\t\tLanding Time:  " << f.getLandingTime_Hour() << ":" << f.getLandingTime_Minutes();
		cout << endl;
		//duration time
		cout << "			\t\t\tDuration Time:  " << f.getTotalFlightTime() << " hour(s) ";
		cout << endl << endl;
	}
};