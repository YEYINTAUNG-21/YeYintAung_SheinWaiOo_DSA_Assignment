/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include <string>
#include <iostream>
#include "RatingList.h"
using namespace std;

struct GameScore {
	string gameName;
	int totalScore;
	int count;
	double average;
};

class Recommendation {
private:
	RatingList* ratingList;
	static const int LIKE_THRESHOLD = 6;
	static const int TOP_GAMES = 5;
	static const int MAX_MEMBERS = 1000;
	static const int MAX_GAMES = 10000;

	void mergeSort(GameScore scores[], int n);
	void mergeSort(GameScore scoress[], int first, int last);
	void merge(GameScore scores[], int first, int mid, int last);
	bool containsMember(string scores[], int size, const string& memberId) const;

public:
	Recommendation(RatingList& ratingList);
	void recommendGames(const string& targetGameName);
};