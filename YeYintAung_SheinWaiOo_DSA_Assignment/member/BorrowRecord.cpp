/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
#include "BorrowRecord.h"

/*
Purpose: Initialize an empty borrow record.
Parameters: None.
Returns: None.
*/
BorrowRecord::BorrowRecord() : memberId(""), gameName(""), returned(false) {
}

/*
Purpose: Initialize a borrow record with member and game info.
Parameters:
- memberId: Member ID of borrower.
- gameName: Name of the borrowed game.
Returns: None.
*/
BorrowRecord::BorrowRecord(const std::string& memberId, const std::string& gameName)
    : memberId(memberId), gameName(gameName), returned(false) {
}

/*
Purpose: Get the member ID of the borrower.
Parameters: None.
Returns: Member ID string.
*/
std::string BorrowRecord::getMemberId() const {
    return memberId;
}

/*
Purpose: Get the borrowed game name.
Parameters: None.
Returns: Game name string.
*/
std::string BorrowRecord::getGameName() const {
    return gameName;
}

/*
Purpose: Check if the record is marked returned.
Parameters: None.
Returns: True if returned, otherwise false.
*/
bool BorrowRecord::isReturned() const {
    return returned;
}

/*
Purpose: Mark the record as returned.
Parameters: None.
Returns: None.
*/
void BorrowRecord::markReturned() {
    returned = true;
}