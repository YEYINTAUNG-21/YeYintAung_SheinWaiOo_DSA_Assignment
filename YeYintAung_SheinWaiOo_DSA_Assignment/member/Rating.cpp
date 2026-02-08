/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
#include "Rating.h"

/*
Purpose: Initialize an empty rating.
Parameters: None.
Returns: None.
*/
Rating::Rating() : memberId(""), gameName(""), rating(0), comment("") {
}

/*
Purpose: Initialize a rating with member, game, value, and comment.
Parameters:
- memberId: Member ID who rated.
- gameName: Game being rated.
- rating: Rating value.
- comment: Review text.
Returns: None.
*/
Rating::Rating(const string& memberId, const string& gameName, int rating, const string& comment)
    : memberId(memberId), gameName(gameName), rating(rating), comment(comment) {
}

/*
Purpose: Get the member ID of the rating.
Parameters: None.
Returns: Member ID string.
*/
string Rating::getMemberId() const {
    return memberId;
}

/*
Purpose: Get the game name of the rating.
Parameters: None.
Returns: Game name string.
*/
string Rating::getGameName() const {
    return gameName;
}

/*
Purpose: Get the rating value.
Parameters: None.
Returns: Rating integer.
*/
int Rating::getRating() const {
    return rating;
}

/*
Purpose: Get the review comment.
Parameters: None.
Returns: Comment string.
*/
string Rating::getComment() const {
    return comment;
}