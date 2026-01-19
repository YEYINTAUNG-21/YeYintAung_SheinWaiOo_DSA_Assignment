/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include<string>
#include<iostream>
using namespace std;

class Game
{
private:
	string gameName;
	int minPlayers;
	int maxPlayers;
	int minPlayTime;
	int maxPlayTime;
	int yearPublished;

public:
	Game();
	Game(const string& name, int minP, int maxP, int minT, int maxT, int year);

	string getName() const;
	string getMinPlayer() const;
	string getMaxPlayer() const;
	string getMinPlayTime() const;
	string getMaxPlayTime() const;
	string getYearPublished() const;
};