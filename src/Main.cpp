#include "Graph.h"
#include "UserInterface.h"
#include<iostream>
#include<string>
using namespace std;

int main() {
	Graph g("Flights.txt", "HotelCharges_perday.txt");
	UI ui;
	ui.displayMenu(g);
}