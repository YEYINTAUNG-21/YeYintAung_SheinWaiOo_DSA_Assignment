/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
#pragma once
#include <string>

class BorrowRecord {
private:
    std::string memberId;
    std::string gameName;
    bool returned; // false = currently borrowed, true = returned

public:
    BorrowRecord();
    BorrowRecord(const std::string& memberId, const std::string& gameName);

    std::string getMemberId() const;
    std::string getGameName() const;
    bool isReturned() const;

    void markReturned();
};