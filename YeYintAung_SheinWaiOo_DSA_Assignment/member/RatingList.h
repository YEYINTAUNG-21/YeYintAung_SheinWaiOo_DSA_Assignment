/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
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

        /*
    Purpose: Find a review by member ID and game name.
    Parameters:
    - memberId: Member ID to match.
    - gameName: Game name to match.
    Returns: Pointer to matching node, or nullptr if not found.
    */
    Node* findReview(const string& memberId, const string& gameName);

public:

    /*
    Purpose: Get the head node (for recommendation).
    Parameters: None.
    Returns: Pointer to head node.
    */
    Node* getHead() const;// need for recommendation feature

    /*
    Purpose: Initialize an empty rating list.
    Parameters: None.
    Returns: None.
    */
    RatingList();

    /*
    Purpose: Destroy the rating list and free all nodes.
    Parameters: None.
    Returns: None.
    */
    ~RatingList();

    /*
    Purpose: Add a rating record to the list.
    Parameters:
    - rating: Rating record to add.
    Returns: None.
    */
    void addRecord(const Rating& rating);

    /*
   Purpose: Add or update a review for a game by a member.
   Parameters:
   - memberId: Member ID creating the review.
   - memberList: Member list for validation.
   - gameList: Game list for validation.
   Returns: True if review saved, otherwise false.
   */
    bool addReview(const string& memberId, const MemberList& memberList, const GameList& gameList);
    
    /*
   Purpose: Save ratings to CSV.
   Parameters:
   - filename: Output CSV path.
   Returns: None.
   */
    void saveToCSV(const string& filename) const;

    /*
   Purpose: Recalculate and save average ratings to CSV.
   Parameters:
   - filename: Output CSV path.
   Returns: None.
   */
    void updateAverageRatings(const string& filename) const;

    /*
    Purpose: Get rating summary for a game.
    Parameters:
    - gameName: Game name to summarize.
    - average: Output average rating.
    - total: Output total review count.
    Returns: None.
    */
    void getRatingSummary(const string& gameName, double& average, int& total) const;
    
    /*
    Purpose: Display all reviews for a game.
    Parameters:
    - gameName: Game name whose reviews to display.
    - memberList: Member list for reviewer names.
    Returns: None.
    */
    void displayReviews(const string& gameName, const MemberList& memberList) const;
};