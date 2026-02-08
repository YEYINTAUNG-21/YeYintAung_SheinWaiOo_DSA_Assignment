/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
// BorrowList uses a singly linked list to store borrow records.
// Each borrow action inserts a new BorrowRecord node at the head of the list.
// This allows fast O(1) insertion and preserves full borrow history.

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
    bool borrowGame(const std::string& memberId,
                    const std::string& gameName,
		            const MemberList& memberList,
                    GameList& gameList);

    bool returnGame(const std::string& memberId,
                    const std::string& gameName,
                    GameList& gameList);

    void displayMemberSummary(const std::string& memberId) const;
    void displayActiveBorrows(const std::string& memberId) const;

    // Admin operation
    void displayAllBorrowSummary() const;
    void saveToCSV(const string& filename);
    void addRecord(const BorrowRecord& record);
};