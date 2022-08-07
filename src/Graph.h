#pragma once
#include <iostream>
#include "Flight.h"
#include "Vector.h"
#include "List.h"
#include <fstream>
#include "Stack.h"
#include "makeGraph.h"
#include "FlightUI.h"
#include "ListUI.h"
using namespace std;

#define t "\t\t\t\t\t\t";

struct costInfo {	//Structure to store minimum cost and time values
	double cost;
	string destination;
	Flight parent;
	string source;
	string date;
	Time time;

	costInfo() :cost(99999999), destination("") {
	}
};

class Graph {
	Vector<List> adjList;
	int vertices;
	FlightUI flightUI;

	void Display() { //Func to display graph
		ListUI listUI;

		for (int i = 0; i < vertices; i++) {
			listUI.displayList(adjList[i]);
		}
	}

	int getVertix_num(string sour) { //Func to get index of source in adjList
		for (int i = 0; i < vertices; i++) {
			if (adjList[i].getSource() == sour) {
				return i;
			}
		}
		return -1;
	}

	int minimum(costInfo array[], bool set[])	//Func to calculate minimum value for dijkstra
	{
		double min = 99999999;
		int min_index = 0;
		for (int v = 0; v < vertices; v++)
		{
			if (set[v] == 0 && array[v].cost <= min)
			{
				min = array[v].cost;
				min_index = v;
			}
		}
		return min_index;
	}

	ListNode* getChildLocation(string src, int dest)	//Func to get links of source
	{
		int a = getVertix_num(src);
		ListNode* temp = adjList[a].getHead();
		if (a != -1) {
			for (int i = 1; temp != NULL && i <= dest; i++)
				temp = temp->next;
			return temp;
		}
		temp = NULL;
		return temp;

	}

	double getMinimumFlightRate(Vector<Flight>& flight, string& date, string src, string desti, Time time, string airline) //Func to get flight with minimun cost
	{
		Flight temp;
		double min = 99999999;

		for (int i = 0; i < flight.Size(); i++) {
			static string temp1 = date;

			if (src == desti) {
				if (flight[i].getDate_string() == date && flight[i].getTicketPrice() < min && flight[i].get_Name_of_Airline() == airline) {
					temp = flight[i];
					min = flight[i].getTicketPrice();
				}
			}

			else {
				if (((flight[i].getDate_string() == date && flight[i].getFlyingTime_Hour() > time.getHours()) || (flight[i].getDate_string()[0] > date[0] && flight[i].getDate_string()[1] == '/' && date[1] == '/')) && flight[i].getTicketPrice() < min && flight[i].get_Name_of_Airline() == airline) {
					temp = flight[i];
					min = flight[i].getTicketPrice();
					date = temp.getDate_string();
				}
			}
		}

		return temp.getTicketPrice();
	}

	double getMinimumFlightTime(Vector<Flight>& flight, string& date, string src, string desti, Time time)	//Func to get flight with minimum time
	{
		Flight temp;
		double min = 99999999;
		for (int i = 0; i < flight.Size(); i++) {
			static string temp1 = date;
			if (src == desti) {
				if (flight[i].getDate_string() == date && flight[i].getTotalFlightTime() < min) {
					temp = flight[i];
					min = flight[i].getTotalFlightTime();
				}
			}
			else {
				if (((flight[i].getDate_string() == date && flight[i].getFlyingTime_Hour() > time.getHours()) || (flight[i].getDate_string()[0] > date[0] && flight[i].getDate_string()[1] == '/' && date[1] == '/')) && flight[i].getTotalFlightTime() < min) {
					temp = flight[i];
					min = flight[i].getTotalFlightTime();
					date = temp.getDate_string();
				}
			}
		}
		return temp.getTotalFlightTime();
	}
	Flight getMinimumFlightT(Vector<Flight>& flight, string& date, string src, string desti, Time time) //Func to get minimum flight with minimum time
	{
		Flight temp;
		double min = 99999999;

		for (int i = 0; i < flight.Size(); i++) {
			static string temp1 = date;

			if (src == desti) {
				if (flight[i].getDate_string() == date && flight[i].getTotalFlightTime() < min) {
					temp = flight[i];
					min = flight[i].getTicketPrice();
				}
			}

			else {
				if (((flight[i].getDate_string() == date && flight[i].getFlyingTime_Hour() > time.getHours()) || (flight[i].getDate_string()[0] > date[0] && flight[i].getDate_string()[1] == '/' && date[1] == '/')) && flight[i].getTicketPrice() < min) {
					temp = flight[i];
					min = flight[i].getTicketPrice();
					date = temp.getDate_string();
				}
			}
		}

		return temp;
	}
	Flight getMinimumFlight(Vector<Flight>& flight, string& date, string src, string desti, Time time, string airline)	//Func to get minimum flight with minimun cost
	{
		Flight temp;
		double min = 99999999;

		for (int i = 0; i < flight.Size(); i++) {
			static string temp1 = date;

			if (src == desti) {
				if (flight[i].getDate_string() == date && flight[i].getTicketPrice() < min && flight[i].get_Name_of_Airline() == airline) {
					temp = flight[i];
					min = flight[i].getTicketPrice();
				}
			}

			else {
				if (((flight[i].getDate_string() == date && flight[i].getFlyingTime_Hour() > time.getHours()) || (flight[i].getDate_string()[0] > date[0] && flight[i].getDate_string()[1] == '/' && date[1] == '/')) && flight[i].getTicketPrice() < min && flight[i].get_Name_of_Airline() == airline) {
					temp = flight[i];
					min = flight[i].getTicketPrice();
					date = temp.getDate_string();
				}
			}
		}

		return temp;
	}

	double getCost(costInfo* costs, string desti) {
		for (int i = 0; i < vertices; i++) {
			if (costs[i].destination == desti) {
				return costs[i].cost;
			}
		}
	}

	int getCostArrayIndex(string desti, costInfo* costs) {
		for (int i = 0; i < vertices; i++) {
			if (costs[i].destination == desti) {
				return i;
			}
		}
	}

	void displayMinCostPath(string src, string desti, Stack<Flight>& temp, Stack<string>& destination, costInfo* costs, int& index) {
		while (desti != src) {
			for (int i = 0; i < vertices; i++) {
				if (costs[i].destination == desti) {
					if (costs[i].parent.getTicketPrice() != 99999999) {
						temp.push(costs[i].parent);
						destination.push(desti);
						desti = costs[i].source;
						break;
					}
				}

				if (i == vertices - 1) {
					desti = src;
				}
			}
		}
	}

	void displayMinTimePath(string src, string desti, Stack<Flight>& temp, Stack<string>& destination, costInfo* costs, int& index) {
		while (desti != src) {
			for (int i = 0; i < vertices; i++) {
				if (costs[i].destination == desti) {
					if (costs[i].parent.getTicketPrice() != 99999999) {
						temp.push(costs[i].parent);
						destination.push(desti);
						desti = costs[i].source;
						break;
					}
				}

				if (i == vertices - 1) {
					desti = src;
				}
			}
		}
	}

public:
	Graph(string fileName, string hotelfile) :vertices(0) {
		makeGraph mg;
		mg.readFromFile(fileName, hotelfile, vertices, adjList);
	}

	void direct_traversal(string sour, string dest, string date, string airline) { //Scenario 5
		bool check = false;
		int i = getVertix_num(sour);
		if (i == -1) {
			cout << "Origin city not found. ";
			return;
		}
		ListNode* temp = adjList[i].getHead();
		while (temp != NULL) {
			if (temp->destination == dest) {
				cout << "\t-----------------------------------------------------------------------------------------------" << endl;
				cout << "\tSource:  " << sour;
				cout << "						";
				cout << "\tDestination:  " << temp->destination << endl;
				cout << "\t-----------------------------------------------------------------------------------------------" << endl;
				if (date == "0" && airline == "0") {
					check = true;
					temp->flight.print();
					cout << "\tHotel Rate:  " << temp->hotelRate << " " << endl << endl;
				}
				else if (date == "0" && airline != "0") {
					for (int j = 0; j < temp->flight.Size(); j++) {
						if (airline == temp->flight[j].get_Name_of_Airline()) {
							check = true;
							cout << temp->flight[j];
							cout << "\tHotel Rate:  " << temp->hotelRate << " " << endl << endl;
						}
					}
				}
				else if (date != "0" && airline == "0") {
					for (int j = 0; j < temp->flight.Size(); j++) {
						if (date == temp->flight[j].getDate_string()) {
							check = true;
							cout << temp->flight[j];
							cout << "\tHotel Rate:  " << temp->hotelRate << " " << endl << endl;
						}
					}
				}
				else if (date != "0" && airline != "0") {
					for (int j = 0; j < temp->flight.Size(); j++) {
						if (date == temp->flight[j].getDate_string() && airline == temp->flight[j].get_Name_of_Airline()) {
							check = true;
							cout << temp->flight[j];
							cout << "\tHotel Rate:  " << temp->hotelRate << " " << endl << endl;
						}
					}
				}
			}

			temp = temp->next;
		}
		if (!check) {
			cout << "\t\t\t\t\t\tNo Direct flights";
		}
	}


	void connected_traversal(string sour, string trans, string dest, string date) { //Scenario 3
		int check = 0;
		int i = getVertix_num(sour);
		if (i == -1) {
			cout << "\t\t\t\t\tOrigin city not found. ";
			return;
		}
		int count = 1;
		int j;
		int str;
		Time str1;
		Time str2;
		int dur;
		ListNode* temp = adjList[i].getHead();
		while (temp != NULL) {
			if (temp->destination == trans) {
				j = getVertix_num(temp->destination);
				for (int k = 0; k < temp->flight.Size(); k++) {
					if (date == temp->flight[k].getDate_string()) {
						cout << "Option: " << count << endl;
						count++;
						cout << "\t-----------------------------------------------------------------------------------------------" << endl;
						cout << "\tSource:  " << sour;
						cout << "						";
						cout << "\tTransit:  " << temp->destination << endl;
						cout << "\t-----------------------------------------------------------------------------------------------" << endl;
						str = temp->flight[k].getDay_of_Flight();                //date match
						str1 = temp->flight[k].getFlyingTime();                //storing time
						str2 = temp->flight[k].getLandingTime();
						dur = temp->flight[k].get_Total_Air_Time();
						cout << temp->flight[k];
						cout << "\tHotel Rate:  " << temp->hotelRate << " " << endl << endl;
						ListNode* temp1 = adjList[j].getHead();
						while (temp1 != NULL) {
							if (temp1->destination == dest) {
								cout << "\t-----------------------------------------------------------------------------------------------" << endl;
								cout << "\tTransit:  " << trans;
								cout << "						";
								cout << "\tDestination:  " << temp1->destination << endl;
								cout << "\t-----------------------------------------------------------------------------------------------" << endl;
								for (int k = 0; k < temp1->flight.Size(); k++) {
									if (str == temp1->flight[k].getDay_of_Flight()) {
										if (temp1->flight[k].getFlyingTime_Hour() > (str1.getHours() + dur)) {
											check = 1;
											cout << temp1->flight[k];
											cout << t;
											cout << "Transit stay duration: " << temp1->flight[k].getFlyingTime_Hour() - str2.getHours() << " Hours(s)" << endl << endl;
										}
									}
									else if (str < temp1->flight[k].getDay_of_Flight()) {
										check = 1;
										cout << temp1->flight[k];
										cout << t;
										cout << "Transit Flight will fly after this date" << endl << endl;
									}


								}
								if (check == 1) {
									cout << endl;
									cout << "\tHotel Rate:  " << temp1->hotelRate << " " << endl << endl;
								}

							}
							temp1 = temp1->next;
						}

					}
				}
			}
			temp = temp->next;
		}

		if (check == 0) {
			cout << "\t\t\t\tThere are no connecting flights with the given transit location." << endl;
		}
	}

	void transit_time(string sour, string trans, string dest, int t_hour, string date) { //Scenario 4
		int check = 0;
		int i = getVertix_num(sour);
		if (i == -1) {
			cout << "\t\t\t\t\tOrigin city not found. ";
			return;
		}
		int count = 1;
		int stay_hour;
		int j;
		int str;
		Time str1;
		Time str2;
		int dur;
		int trans_check = 0;
		ListNode* temp = adjList[i].getHead();
		while (temp != NULL) {
			if (temp->destination == trans) {
				j = getVertix_num(temp->destination);
				for (int k = 0; k < temp->flight.Size(); k++) {
					if (date == temp->flight[k].getDate_string()) {
						cout << "Option: " << count << endl;
						count++;
						cout << "\t-----------------------------------------------------------------------------------------------" << endl;
						cout << "\tSource:  " << sour;
						cout << "						";
						cout << "\tTransit:  " << temp->destination << endl;
						cout << "\t-----------------------------------------------------------------------------------------------" << endl;
						str = temp->flight[k].getDay_of_Flight();                //date match
						str1 = temp->flight[k].getFlyingTime();                //storing time
						str2 = temp->flight[k].getLandingTime();
						dur = temp->flight[k].get_Total_Air_Time();
						cout << temp->flight[k];
						cout << "\tHotel Rate:  " << temp->hotelRate << " " << endl << endl;
						ListNode* temp1 = adjList[j].getHead();
						while (temp1 != NULL) {
							if (temp1->destination == dest) {
								cout << "\t-----------------------------------------------------------------------------------------------" << endl;
								cout << "\tTransit:  " << trans;
								cout << "						";
								cout << "\tDestination:  " << temp1->destination << endl;
								cout << "\t-----------------------------------------------------------------------------------------------" << endl;
								for (int k = 0; k < temp1->flight.Size(); k++) {
									stay_hour = temp1->flight[k].getFlyingTime_Hour() - str2.getHours();
									if (str == temp1->flight[k].getDay_of_Flight() && t_hour != 12) {
										if (temp1->flight[k].getFlyingTime_Hour() > (str1.getHours() + dur) && stay_hour == t_hour) {
											cout << t;
											cout << "Flights with " << t_hour << " hour(s) duration are : " << endl;
											check = 1;
											trans_check = 1;
											cout << temp1->flight[k];

										}
									}
									else if (str < temp1->flight[k].getDay_of_Flight() && t_hour == 12) {
										check = 1;
										trans_check = 1;
										cout << temp1->flight[k];
										cout << t;
										cout << "Transit Flight will fly on next day" << endl << endl;
									}
									else {
										trans_check = 0;
									}


								}
								if (check == 1) {
									cout << endl;
									cout << "\tHotel Rate:  " << temp1->hotelRate << " " << endl << endl;
								}
								if (trans_check == 0) {
									cout << "\t\t\tThere are no more transit flights with given transit time duration." << endl;
								}

							}
							temp1 = temp1->next;
						}

					}
				}
			}
			temp = temp->next;
		}

		if (check == 0) {
			cout << "\t\t\t\tThere are no connecting flights with the given transit location." << endl;
		}
	}

	costInfo* dijkstra(string src, string date, string airline) { //Scenario 1
		costInfo* costs = new costInfo[vertices];
		bool* Set = new bool[vertices];
		string tempDate;
		Time time;

		for (int i = 0; i < vertices; i++) {
			Set[i] = 0;
			costs[i].destination = adjList[i].getSource();
			costs[i].date = date;
		}

		costs[getVertix_num(src)].cost = 0;

		for (int i = 0; i < vertices - 1; i++) {
			int index = minimum(costs, Set);
			Set[index] = 1;

			for (int v = 0; v < vertices; v++)
			{
				Date d1;
				double rate;

				date = costs[getCostArrayIndex(costs[index].destination, costs)].date;
				tempDate = costs[getCostArrayIndex(costs[index].destination, costs)].date;
				time = costs[getCostArrayIndex(costs[index].destination, costs)].time;
				ListNode* Location = getChildLocation(costs[index].destination, v);

				if (Location != NULL) {
					d1 = getMinimumFlight(getChildLocation(costs[index].destination, v)->flight, tempDate, src, costs[index].destination, time, airline).getDate();
					tempDate = costs[getCostArrayIndex(costs[index].destination, costs)].date;
					rate = getChildLocation(costs[index].destination, v)->hotelRate;

					string truedate = "";
					int day = 0, day1;
					for (int i = 0; date[i] != '/'; i++)
					{
						truedate += date[i];
					}
					day = stoi(truedate);
					day1 = d1.getDay();

					if (day1 != 99999999) {
						rate = (day1 - day) * rate;
					}

					else {
						rate = 0;
					}
				}

				if (Location && ((rate + costs[index].cost + getMinimumFlightRate(getChildLocation(costs[index].destination, v)->flight, date, src, costs[index].destination, time, airline)) <= getCost(costs, getChildLocation(costs[index].destination, v)->destination)))
				{
					int j = getCostArrayIndex(getChildLocation(costs[index].destination, v)->destination, costs);
					costs[j].cost = costs[index].cost + getMinimumFlightRate(getChildLocation(costs[index].destination, v)->flight, tempDate, src, costs[index].destination, time, airline) + rate;
					tempDate = costs[getCostArrayIndex(costs[index].destination, costs)].date;
					costs[j].parent = getMinimumFlight(getChildLocation(costs[index].destination, v)->flight, tempDate, src, costs[index].destination, time, airline);
					costs[j].source = costs[index].destination;
					costs[j].date = date;
					costs[j].time = costs[j].parent.getLandingTime();
				}

				if (!Location) {
					break;
				}
			}
		}
		delete[] Set;
		return costs;
	}

	costInfo* MinimumTimeQuery(string src, string date) //Scenario 2
	{
		costInfo* times = new costInfo[vertices];
		bool* Set = new bool[vertices];
		string tempDate = date;
		Time time;

		for (int i = 0; i < vertices; i++) {
			Set[i] = 0;
			times[i].destination = adjList[i].getSource();
			times[i].date = date;
		}
		times[getVertix_num(src)].cost = 0;

		for (int i = 0; i < vertices - 1; i++) {
			int index = minimum(times, Set);
			Set[index] = 1;


			for (int v = 0; v < vertices; v++)
			{
				date = times[getCostArrayIndex(times[index].destination, times)].date;
				time = times[getCostArrayIndex(times[index].destination, times)].time;
				ListNode* Location = getChildLocation(times[index].destination, v);

				if (Location && times[index].cost + getMinimumFlightTime(getChildLocation(times[index].destination, v)->flight, date, src, times[index].destination, time) <= getCost(times, getChildLocation(times[index].destination, v)->destination))
				{
					int j = getCostArrayIndex(getChildLocation(times[index].destination, v)->destination, times);
					times[j].cost = times[index].cost + getMinimumFlightTime(getChildLocation(times[index].destination, v)->flight, date, src, times[index].destination, time);
					times[j].parent = getMinimumFlightT(getChildLocation(times[index].destination, v)->flight, date, src, times[index].destination, time);
					times[j].source = times[index].destination;
					times[j].date = date;
					times[j].time = times[j].parent.getLandingTime();
				}
				if (!Location) {
					break;
				}
			}
		}

		delete[] Set;
		return times;
	}

	void findMinTimePath(string src, string desti, string date) { //Scenario 2
		costInfo* costs = MinimumTimeQuery(src, date);
		Stack<Flight> temp;
		Stack<string> destination;
		int index = 0;

		displayMinTimePath(src, desti, temp, destination, costs, index);

		if (temp.isEmpty()) {
			string s = src, d = desti;

			date[0]++;
			costs = MinimumTimeQuery(src, date);

			displayMinTimePath(src, desti, temp, destination, costs, index);

			if (!temp.isEmpty()) {
				index++;
				cout << index;
			}

			while (!temp.isEmpty()) {
				Flight temp1 = temp.pop();
				string temp2 = destination.pop();
				string temp3;

				flightUI.displayFlights(src, temp2, temp1);
				temp3 = costs[getCostArrayIndex(temp2, costs)].source;
				for (int i = 0; i < vertices; i++) {
					if (getChildLocation(temp3, i) && getChildLocation(temp3, i)->destination == temp2) {
						cout << "\tHotel Rate:  " << getChildLocation(temp3, i)->hotelRate << " " << endl << endl;
						break;
					}
				}
				src = temp2;
			}

			src = s;
			desti = d;

			if (date[0] != '2') {
				date[0]--;
				date[0]--;
				costs = MinimumTimeQuery(src, date);

				displayMinTimePath(src, desti, temp, destination, costs, index);
			}

			if (!temp.isEmpty()) {
				index++;
				if (index == 2) {
					cout << endl << endl;
					cout << "------------------------------------------------------------------------------------------";
					cout << "------------------------------";
					cout << endl << endl << endl << endl;
				}
				cout << index;
			}
		}

		if (temp.isEmpty() && index == 0) {
			cout << "No Possible Flight";
			return;
		}

		while (!temp.isEmpty()) {
			Flight temp1 = temp.pop();
			string temp2 = destination.pop();
			string temp3;

			flightUI.displayFlights(src, temp2, temp1);
			temp3 = costs[getCostArrayIndex(temp2, costs)].source;
			for (int i = 0; i < vertices; i++) {
				if (getChildLocation(temp3, i) && getChildLocation(temp3, i)->destination == temp2) {
					cout << "\tHotel Rate:  " << getChildLocation(temp3, i)->hotelRate << " " << endl << endl;
					break;
				}
			}
			src = temp2;
		}
	}
	void findMinCostPath(string src, string desti, string date, string airline) { //Scenario 1
		costInfo* costs = dijkstra(src, date, airline);
		Stack<Flight> temp;
		Stack<string> destination;
		int index = 0;

		displayMinCostPath(src, desti, temp, destination, costs, index);

		if (temp.isEmpty()) {
			string s = src, d = desti;

			date[0]++;
			costs = dijkstra(src, date, airline);

			displayMinCostPath(src, desti, temp, destination, costs, index);

			if (!temp.isEmpty()) {
				index++;
				cout << endl << endl << index;
			}

			while (!temp.isEmpty()) {
				Flight temp1 = temp.pop();
				string temp2 = destination.pop();
				string temp3;

				flightUI.displayFlights(src, temp2, temp1);
				temp3 = costs[getCostArrayIndex(temp2, costs)].source;
				for (int i = 0; i < vertices; i++) {
					if (getChildLocation(temp3, i) && getChildLocation(temp3, i)->destination == temp2) {
						cout << "\tHotel Rate:  " << getChildLocation(temp3, i)->hotelRate << " " << endl << endl;
						break;
					}
				}
				src = temp2;
			}

			src = s;
			desti = d;

			if (date[0] != '2') {
				date[0]--;
				date[0]--;
				costs = dijkstra(src, date, airline);

				displayMinCostPath(src, desti, temp, destination, costs, index);
			}

			if (!temp.isEmpty()) {
				index++;
				if (index == 2) {
					cout << endl;
					cout << "------------------------------------------------------------------------------------------";
					cout << "------------------------------";
					cout << endl << endl << endl;
				}
				cout << index;
			}
		}

		if (temp.isEmpty() && index == 0) {
			cout << "\t\t\t\t\tNo Possible Flight";
			return;
		}

		while (!temp.isEmpty()) {
			Flight temp1 = temp.pop();
			string temp2 = destination.pop();
			string temp3;

			flightUI.displayFlights(src, temp2, temp1);
			temp3 = costs[getCostArrayIndex(temp2, costs)].source;
			for (int i = 0; i < vertices; i++) {
				if (getChildLocation(temp3, i) && getChildLocation(temp3, i)->destination == temp2) {
					cout << "\tHotel Rate:  " << getChildLocation(temp3, i)->hotelRate << " " << endl << endl;
					break;
				}
			}
			src = temp2;
		}
	}
};