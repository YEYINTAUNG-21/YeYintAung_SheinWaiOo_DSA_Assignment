/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
// BorrowRecord represents a single borrowing transaction.
// Each record stores:
// - memberId: who borrowed the game
// - gameName: which game was borrowed
// - returned flag: whether the game has been returned

#pragma once
#include <string>

class BorrowRecord {
private:
    std::string memberId;
    std::string gameName;
    bool returned; // false = currently borrowed, true = returned

public:
    /*
    Purpose: Initialize an empty borrow record.
    Parameters: None.
    Returns: None.
    */
    BorrowRecord();
    /*
    Purpose: Initialize a borrow record with member and game info.
    Parameters:
    - memberId: Member ID of borrower.
    - gameName: Name of the borrowed game.
    Returns: None.
    */
    BorrowRecord(const std::string& memberId, const std::string& gameName);

    /*
    Purpose: Get the member ID of the borrower.
    Parameters: None.
    Returns: Member ID string.
    */
    std::string getMemberId() const;

    /*
    Purpose: Get the borrowed game name.
    Parameters: None.
    Returns: Game name string.
    */
    std::string getGameName() const;

    /*
    Purpose: Check if the record is marked returned.
    Parameters: None.
    Returns: True if returned, otherwise false.
    */
    bool isReturned() const;

    /*
    Purpose: Mark the record as returned.
    Parameters: None.
    Returns: None.
    */
    void markReturned();
};