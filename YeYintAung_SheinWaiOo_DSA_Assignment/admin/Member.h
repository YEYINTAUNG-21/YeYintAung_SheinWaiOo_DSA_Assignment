/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include<string>
#include<iostream>
using namespace std;

class Member
{
private:
	string memberId;
	string memberName;

public:
	Member();
	Member(const string& memberId, const string& memberName);

	string getId() const;
	string getName() const;
};