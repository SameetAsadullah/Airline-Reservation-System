#pragma once
#include <iostream>
#include "Vector.h"
#include <fstream>
#include "List.h"
#include <string>
using namespace std;

class makeGraph {
public:
	void readFromFile(string fileName, string hotelfile, int& vertices, Vector<List>& adjList) {	//Reading data from file
		string data, destination, source;
		double hotelRate;
		string read;

		int c_count = 0;
		ifstream file;

		file.open(hotelfile, ios::in);

		while (getline(file, read)) {
			c_count++;
		}
		file.close();

		string* cities = new string[c_count];
		double* Rate = new double[c_count];
		int i = 0;

		file.open(hotelfile, ios::in);

		while (!file.eof()) {
			file >> read;
			cities[i] = read;
			adjList[i].setSource(cities[i]);	/*Setting cities as vector sources*/
			file >> read;
			Rate[i] = stod(read);
			i++;
		}

		ifstream f1(fileName);

		if (f1.good()) {
			while (!f1.eof()) {
				Flight flight;
				string temp;
				int count = 0;
				bool check = false;

				f1 >> data;
				source = data;
				f1 >> data;
				destination = data;
				f1 >> data;

				for (int i = 0; data[i] != '\0'; i++) {
					if (data[i] != '/') {
						temp += data[i];
					}

					if (data[i] == '/' || data[i + 1] == '\0') {
						if (count == 0) {
							flight.getDate().setDay(stoi(temp));
							count++;
							temp = "";
						}

						else if (count == 1) {
							flight.getDate().setMonth(stoi(temp));
							count++;
							temp = "";
						}

						else {
							flight.getDate().setYear(stoi(temp));
							temp = "";
						}
					}
				}

				count = 0;
				f1 >> data;

				for (int i = 0; data[i] != '\0'; i++) {
					if (data[i] != ':') {
						temp += data[i];
					}

					if (data[i] == ':' || data[i + 1] == '\0') {
						if (count == 0) {
							flight.getFlyingTime().setHours(stoi(temp));
							count++;
							temp = "";
						}

						else if (count == 1) {
							flight.getFlyingTime().setMinutes(stoi(temp));
							temp = "";
						}
					}
				}

				f1 >> data;
				count = 0;

				for (int i = 0; data[i] != '\0'; i++) {
					if (data[i] != ':') {
						temp += data[i];
					}
					if (data[i] == ':' || data[i + 1] == '\0') {
						if (count == 0) {
							flight.getLandingTime().setHours(stoi(temp));
							count++;
							temp = "";
						}
						else if (count == 1) {
							flight.getLandingTime().setMinutes(stoi(temp));
							temp = "";
						}

					}
				}

				f1 >> data;
				flight.setTicketPrice(stoi(data));
				f1 >> data;
				flight.set_Name_of_airline(data);

				for (int i = 0; i < c_count; i++) {
					if (destination == cities[i]) {
						hotelRate = Rate[i];
						break;
					}
				}
				for (int i = 0; i < adjList.Size(); i++)
				{
					if (adjList[i].getSource() == source)
					{
						bool exists = false;
						ListNode* SubHeads = adjList[i].getHead();
						while (SubHeads != NULL) {
							if (SubHeads->destination == destination)
							{
								SubHeads->flight.insert(flight);
								exists = true;
								check = true;
							}
							SubHeads = SubHeads->next;
						}
						if (exists == false)
						{
							adjList[i].insert(flight, destination, hotelRate);
							check = true;
						}
					}
				}
				if (check == false) {
					List l1;
					adjList.insert(l1);
					adjList[vertices].setSource(source);
					adjList[vertices].insert(flight, destination, hotelRate);
					vertices++;
				}
			}
			vertices = 11;
		}

		else {
			cout << "File not opened" << endl;
		}
		f1.close();
	}
};