#include "Rating.h"

Rating::Rating() : memberId(""), gameName(""), rating(0), comment("") {
}

Rating::Rating(const string& memberId, const string& gameName, int rating, const string& comment)
    : memberId(memberId), gameName(gameName), rating(rating), comment(comment) {
}

string Rating::getMemberId() const {
    return memberId;
}

string Rating::getGameName() const {
    return gameName;
}

int Rating::getRating() const {
    return rating;
}

string Rating::getComment() const {
    return comment;
}