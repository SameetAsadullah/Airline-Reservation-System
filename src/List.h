#pragma once
#include<iostream>
#include"Vector"
using namespace std;

class ListNode {
public:
	string destination;
	double hotelRate;
	ListNode* next;
	Vector<Flight> flight;

	ListNode() : destination(""), hotelRate(-1), next(NULL) {
	}
};

class List {
private:
	ListNode* head;
	ListNode* cursor;
	string source;

public:
	List() {
		head = NULL;
		cursor = NULL;
		source = "";
	}

	void setSource(const string& s) {
		source = s;
	}

	string getSource() const {
		return source;
	}

	ListNode* getHead() {
		return head;
	}

	void insert(const Flight& obj, const string& dest, const double& hR) {
		if (head == NULL) {
			head = new ListNode;
			head->flight.insert(obj);
			head->destination = dest;
			head->hotelRate = hR;
			cursor = head;
		}

		else {
			cursor = head;
			while (cursor->next != NULL) {
				cursor = cursor->next;
			}

			cursor->next = new ListNode;
			cursor->next->flight.insert(obj);
			cursor->next->destination = dest;
			cursor->next->hotelRate = hR;
			cursor = cursor->next;
		}
	}

	void clear() {
		cursor = head;
		while (cursor != NULL) {
			ListNode* temp = cursor;
			cursor = cursor->next;
			delete temp;
		}
		head = cursor;
	}

	bool isEmpty() {
		if (head == NULL) {
			return true;
		}
		return false;
	}

	bool gotoNext() {
		if (cursor->next != NULL) {
			cursor = cursor->next;
			return true;
		}
		return false;
	}

	bool gotoPrior() {
		if (cursor != head) {
			ListNode* temp = head;
			while (temp->next != cursor) {
				temp = temp->next;
			}
			cursor = temp;
			return true;
		}
		return false;
	}

	string getCursor() {
		if (head != NULL) {
			return cursor->destination;
		}
	}

	bool moveCursor(int index) {
		if (head != NULL) {
			ListNode* temp = cursor;
			int size = 1;
			cursor = head;

			while (cursor->next != NULL && index >= size) {
				cursor = cursor->next;
				size++;
			}

			if (cursor->next == NULL && index >= size) {
				cout << "Index out of range" << endl;
				cursor = temp;
				return false;
			}
			return true;
		}
	}

	bool moveCursortoEnd() {
		if (head != NULL) {
			cursor = head;

			while (cursor->next != NULL) {
				cursor = cursor->next;
			}
			return true;
		}
		return false;
	}

	~List() {
		while (head != NULL) {
			ListNode* temp = head;
			head = head->next;
			delete temp;
		}
	}
};