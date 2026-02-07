/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include<string>
#include<iostream>
#include "Member.h"
using namespace std;

const int MAX_MEMBERS = 1000;
class MemberList
{
private:

	struct Node {
		Member data;
		Node* next;
	};

	Node* table[MAX_MEMBERS];

	int hash(const string& memberId) const;

	static void mergeSort(Member members[], int n);
	static void mergeSort(Member members[], int first, int last);
	static void merge(Member members[], int first, int mid, int last);

public:
	MemberList();
	~MemberList();

	void addMember();
	void addMember(const string& id, const string& name);

	bool exists(const string& memberId) const;
	string getMemberName(const string& memberId) const;
	Member* searchMemberById(const string& id);
	void displayAllMembers() const;
	void displaySortedMemberById();
	void saveToCSV(const string& filename) const;
};