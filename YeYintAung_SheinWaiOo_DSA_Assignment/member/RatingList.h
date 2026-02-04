#pragma once
#include<string>
#include<iostream>
#include <limits>
#include "Rating.h"
#include "../admin/GameList.h"
#include "../admin/MemberList.h"
using namespace std;

class RatingList
{
public: // need for recommendation feature
    struct Node {
        Rating data;
        Node* next;
    };

private:
    Node* head;

    Node* findReview(const string& memberId, const string& gameName);

public:

    Node* getHead() const;// need for recommendation feature

    RatingList();
    ~RatingList();

    void addRecord(const Rating& rating);
    bool addReview(const string& memberId, const MemberList& memberList, const GameList& gameList);
    void saveToCSV(const string& filename) const;
    void updateAverageRatings(const string& filename) const;

    void getRatingSummary(const string& gameName, double& average, int& total) const;
    void displayReviews(const string& gameName, const MemberList& memberList) const;
};