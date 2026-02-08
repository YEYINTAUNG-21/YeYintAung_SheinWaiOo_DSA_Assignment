/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
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
    /*
    Purpose: Initialize an empty rating.
    Parameters: None.
    Returns: None.
    */
    Rating();

    /*
    Purpose: Initialize a rating with member, game, value, and comment.
    Parameters:
    - memberId: Member ID who rated.
    - gameName: Game being rated.
    - rating: Rating value.
    - comment: Review text.
    Returns: None.
    */
    Rating(const string& memberId, const string& gameName, int rating, const string& comment);

    /*
    Purpose: Get the member ID of the rating.
    Parameters: None.
    Returns: Member ID string.
    */
    string getMemberId() const;

    /*
    Purpose: Get the game name of the rating.
    Parameters: None.
    Returns: Game name string.
    */
    string getGameName() const;

    /*
    Purpose: Get the rating value.
    Parameters: None.
    Returns: Rating integer.
    */
    int getRating() const;

    /*
    Purpose: Get the review comment.
    Parameters: None.
    Returns: Comment string.
    */
    string getComment() const;
};