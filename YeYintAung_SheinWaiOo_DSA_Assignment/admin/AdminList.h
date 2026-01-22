/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include<string>
#include<iostream>
#include "Admin.h"
using namespace std;

typedef Admin AdminItem;

class AdminList
{
private:
	struct Node
	{
		AdminItem item;
		Node* next;
	};
	Node* firstNode;	
	int  size;		

public:
	AdminList();
	~AdminList();

	void addAdmin(const string& id, const string& name);
	bool login(const string& adminId) const;
	string getAdminName(const string& adminId) const;
};