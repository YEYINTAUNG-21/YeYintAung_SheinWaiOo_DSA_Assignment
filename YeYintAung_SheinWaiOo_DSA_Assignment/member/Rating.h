#pragma once
#include<string>
#include<iostream>
using namespace std;

class Rating
{
private:
    string memberId;
    string gameName;
    int rating;
    string comment;

public:
    Rating();
    Rating(const string& memberId, const string& gameName, int rating, const string& comment);

    string getMemberId() const;
    string getGameName() const;
    int getRating() const;
    string getComment() const;
};