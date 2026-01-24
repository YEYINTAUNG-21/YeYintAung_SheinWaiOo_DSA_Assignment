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

const int TABLE_SIZE = 101;
class MemberList
{
private:

	struct Node {
		Member data;
		Node* next;
	};

	Node* table[TABLE_SIZE];

	int hash(const string& memberId) const;
public:
	MemberList();
	~MemberList();

	void addMember();                           
	void addMember(const string& id, const string& name);

	bool exists(const string& memberId) const;   
	string getMemberName(const string& memberId) const;
};