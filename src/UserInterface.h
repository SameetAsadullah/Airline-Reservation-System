#pragma once
#include<iostream>
#include<string>
#include"Graph.h"
#include"Flight.h"
using namespace std;

class UI {
public:
	void displayMenu(Graph &g) {
		cout << "================ FLIGHT RESERVATION SYSTEM ================" << endl << endl;
		int a = -1;
		while (a != 0) {
			cout << "What type of search do u want?" << endl << endl;
			cout << "------	1:- Basic Search" << endl;
			cout << "------	2:- Advanced Search" << endl;
			cout << "------	Enter 0 if you dont want any more queries " << endl;
			cin >> a;

			if (a == 1) {
				int b;
				cout << " Press 1 for Direct Flights with specific date and airline. " << endl;
				cout << " Press 2 for connected Flight with specific transit location on a specific date. " << endl;
				cin >> b;
				if (b == 1) {
					string source_city;
					string dest_city;
					string date;
					string airline;
					cout << " Enter Origin city:";
					cin >> source_city;
					cout << " Enter destination city:";
					cin >> dest_city;
					cout << " Enter travel date, Enter 0 if you dont want to give any specific date: ";
					cin >> date;
					cout << " Enter airline, Enter 0 if you dont want to give any specific airline: ";
					cin >> airline;
					g.direct_traversal(source_city, dest_city, date, airline);

				}
				else if (b == 2) {
					string source, transit, dest, date;
					cout << " Enter Origin city: ";
					cin >> source;
					cout << " Enter Transit Location: ";
					cin >> transit;
					cout << " Enter Destination City: ";
					cin >> dest;
					cout << " Enter date of departure: ";
					cin >> date;
					g.connected_traversal(source, transit, dest, date);
					g.transit_time(source, transit, dest, 1, date);
				}
				cout << endl;
				cout << "		Do you have any more queries? " << endl;
			}

			else if (a == 2) {
				int b;
				cout << " Press 1 for flights with minimum travel cost. " << endl;
				cout << " Press 2 for flights with minimum travel time. " << endl;
				cout << " Press 3 for connected flights with specific location, duration and date. " << endl;
				cin >> b;
				if (b == 1) {
					string source, dest, date, airline;
					cout << " Enter Origin city: ";
					cin >> source;
					cout << " Enter Destination City: ";
					cin >> dest;
					cout << " Enter date of departure: ";
					cin >> date;
					cout << " Enter airline name: ";
					cin >> airline;
					g.findMinCostPath(source, dest, date, airline);

				}
				else if (b == 2) {
					string source, dest, date, airline;
					cout << " Enter Origin city: ";
					cin >> source;
					cout << " Enter Destination City: ";
					cin >> dest;
					cout << " Enter date of departure: ";
					cin >> date;
					g.findMinTimePath(source, dest, date);

				}
				else if (b == 3) {
					string source, transit, dest, date;
					int hour;
					cout << " Enter Origin city: ";
					cin >> source;
					cout << " Enter Transit Location: ";
					cin >> transit;
					cout << " Enter Destination City: ";
					cin >> dest;
					cout << " Enter date of departure: ";
					cin >> date;
					cout << "Enter stay duration hours less than 12, enter 12 if you want to stay for more than 12 hours: ";
					cin >> hour;
					g.transit_time(source, transit, dest, hour, date);
				}
				cout << endl;
				cout << "		Do you have any more queries? " << endl;

			}
		}
	}
};