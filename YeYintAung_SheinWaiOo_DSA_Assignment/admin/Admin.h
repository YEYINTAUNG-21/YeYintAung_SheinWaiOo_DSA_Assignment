/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include<string>
#include<iostream>
using namespace std;

class Admin
{
private:
	string adminId;
	string name;

public:
	Admin();
	Admin(const string& id, const string& name);

	string getId() const;
	string getName() const;
};