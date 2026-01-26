/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
#pragma once
#include <string>
#include "../admin/GameList.h"
#include "../admin/MemberList.h"
#include "BorrowRecord.h"

class BorrowList {
private:
    struct Node {
        BorrowRecord data;
        Node* next;
    };

    Node* head;
    Node* findActiveBorrow(const std::string& memberId, const std::string& gameName) const;

public:
    BorrowList();
    ~BorrowList();

    // Member operations
    void borrowGame(const std::string& memberId,
                    const std::string& gameName,
		            const MemberList& memberList,
                    GameList& gameList);

    void returnGame(const std::string& memberId,
                    const std::string& gameName,
                    GameList& gameList);

    void displayMemberSummary(const std::string& memberId) const;

    // Admin operation
    void displayAllBorrowSummary() const;
};