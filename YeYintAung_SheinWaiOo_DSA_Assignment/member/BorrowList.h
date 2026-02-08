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
    /*
    Purpose: Find an active (not returned) borrow record for a member and game.
    Parameters:
    - memberId: Member ID to match.
    - gameName: Game name to match.
    Returns: Pointer to matching node, or nullptr if not found.
    */
    // findActiveBorrow():
    // Traverses the borrow linked list to locate an active borrow record
    // (returned == false) that matches the given member ID and game name.
    // Returns a pointer to the matching node if found, otherwise nullptr.
    Node* findActiveBorrow(const std::string& memberId, const std::string& gameName) const;

public:
    BorrowList();
    ~BorrowList();

    // Member operations
    //borrowGame();
     /*
    Purpose: Borrow a game and record the transaction.
    Parameters:
    - memberId: Member ID who borrows the game.
    - gameName: Game to borrow.
    - memberList: Member list for validation.
    - gameList: Game list for availability updates.
    Returns: True if borrow succeeds, otherwise false.
    */
    bool borrowGame(const std::string& memberId,
                    const std::string& gameName,
		            const MemberList& memberList,
                    GameList& gameList);

    // returnGame():
    /*
    Purpose: Return a borrowed game and update inventory.
    Parameters:
    - memberId: Member ID returning the game.
    - gameName: Game to return.
    - gameList: Game list for inventory updates.
    Returns: True if return succeeds, otherwise false.
    */
    // Handles the process of returning a borrowed board game.
    // The function locates an active borrow record for the given member and game,
    // marks the record as returned, restores the game's copy count in the BST,
    // and saves the updated data to CSV files.

    bool returnGame(const std::string& memberId,
                    const std::string& gameName,
                    GameList& gameList);

    /*
    Purpose: Display all borrow/return records for a specific member.
    Parameters:
    - memberId: Member ID whose records to display.
    Returns: None.
    */
    void displayMemberSummary(const std::string& memberId) const;
    
    /*
    Purpose: Display only active (not returned) borrows for a member.
    Parameters:
    - memberId: Member ID whose active borrows to display.
    Returns: None.
    */
    // displayActiveBorrows():
    // Traverses the singly linked list of borrow records and displays
    // all active borrow entries (returned == false) for the specified member.
    // This function is used to guide the member during the return process.
    void displayActiveBorrows(const std::string& memberId) const;

    /*
    Name: Ye Yint Aung
    Group - 3
    Student ID - S10268975C
    */
    /*
    Purpose: Display all borrow records (admin view).
    Parameters: None.
    Returns: None.
    */
    // Admin operation
    void displayAllBorrowSummary() const;

    /*
    Purpose: Save all borrow records to CSV.
    Parameters:
    - filename: Output CSV path.
    Returns: None.
    */
    void saveToCSV(const string& filename);

    /*
    Purpose: Add a borrow record node to the list.
    Parameters:
    - record: Borrow record to add.
    Returns: None.
    */
    void addRecord(const BorrowRecord& record);
};