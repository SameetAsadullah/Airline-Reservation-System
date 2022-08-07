#pragma once
#include "List.h"

class ListUI {
public:
	void displayList(List& l) {
		ListNode* temp = l.getHead();

		while (temp != NULL) {
			cout << "\t-----------------------------------------------------------------------------------------------" << endl;
			cout << "\tSource:  " << l.getSource();
			cout << "						";
			cout << "\tDestination:  " << temp->destination << endl;
			cout << "\t-----------------------------------------------------------------------------------------------" << endl;
			temp->flight.print();
			cout << "\tHotel Rate:  " << temp->hotelRate << " " << endl << endl;
			system("pause");
			temp = temp->next;
		}
		cout << endl;
	}
};