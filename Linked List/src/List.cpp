#include "List.h"

List::List() : head(nullptr) {}

List::~List() {

	while (head != nullptr) {

		if (head->next != nullptr) {

			head = head->next;
			delete head->prev;
		} else {

			delete head;
			head = nullptr;
		}
	}
}

bool List::Insert(string data) {

	bool result;

	Node *cur = new Node();

	if (cur == nullptr)
		result = false;
	else {

		result = true;
		cur->data = data;

		if (head == nullptr) {

			cur->prev = nullptr;
			cur->next = nullptr;
			head = cur;
		} else {

			Node *lastNode;

			for (lastNode = head; lastNode->next != nullptr && lastNode->next->data < data; lastNode = lastNode->next);

			if (lastNode->next == nullptr && lastNode->data < data)
				insertBack(lastNode, cur);
			else if (lastNode->prev == nullptr && lastNode->data > data)
				insertFront(cur);
			else
				insertMiddle(lastNode, cur);
		}
	}

	return result;
}

void List::insertFront(Node *cur) {

	head->prev = cur;
	cur->next = head;
	cur->prev = nullptr;
	head = cur;
}

void List::insertBack(Node *lastNode, Node *cur) {

	lastNode->next = cur;
	cur->prev = lastNode;
	cur->next = nullptr;
}

void List::insertMiddle(Node *lastNode, Node *cur) {

	cur->next = lastNode->next;
	cur->next->prev = cur;
	cur->prev = lastNode;
	lastNode->next = cur;
}

bool List::Delete(string data) {

	bool result;

	if (head == nullptr)
		result = false;
	else {

		Node *lastNode;

		for (lastNode = head; lastNode->next != nullptr && lastNode->data != data; lastNode = lastNode->next);

		if (lastNode->data != data)
			result = false;
		else {

			if (lastNode->prev == nullptr)
				deleteFront();
			else if (lastNode->next == nullptr)
				deleteBack(lastNode);
			else
				deleteMiddle(lastNode);

			result = true;
		}
	}

	return result;
}

void List::deleteFront() {

	if (head->next != nullptr) {

		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	} else {

		delete head;
		head = nullptr;
	}
}

void List::deleteBack(Node *cur) {

	if (cur->prev != nullptr) {

		cur = cur->prev;
		delete cur->next;
		cur->next = nullptr;
	} else {

		delete cur;
		head = nullptr;
	}
}

void List::deleteMiddle(Node *cur) {

	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;

	delete cur;
}

bool List::Edit(string previousData, string newData) {

	return (Delete(previousData) && Insert(newData));
}

void List::Print() {

	if (head != nullptr) {

		for (Node *cur = head; cur != nullptr; cur = cur->next)
			cout << cur->data << endl;
	}
}