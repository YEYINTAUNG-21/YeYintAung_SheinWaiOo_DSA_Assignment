#include "BorrowList.h"
#include <iostream>
#include <fstream>
#include <sstream>

BorrowList::BorrowList() : head(nullptr) {
    // Initialize empty linked list for borrow records
}

BorrowList::~BorrowList() {
    // Free all nodes in the linked list
    Node* curr = head;
    while (curr != nullptr) {
        Node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
    head = nullptr;
}

BorrowList::Node* BorrowList::findActiveBorrow(const std::string& memberId, const std::string& gameName) const {
    // Traverse list to find an active (not yet returned) borrow for this member/game
    Node* curr = head;
    while (curr != nullptr) {
        if (!curr->data.isReturned() &&
            curr->data.getMemberId() == memberId &&
            curr->data.getGameName() == gameName) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool BorrowList::borrowGame(const std::string& memberId,
                            const std::string& gameName,
                            const MemberList& memberList,
                            GameList& gameList) {
    // Validate the member exists before recording a borrow
    if (!memberList.exists(memberId)) {
        std::cout << "Member not found.\n";
        return false;
    }

    // Check game exists and has available copies
    Game* game = gameList.searchGameByName(gameName);
    if (game == nullptr) {
        std::cout << "Game not found.\n";
        return false;
    }
    if (game->getCopies() <= 0) {
        std::cout << "No available copies.\n";
        return false;
    }

    // Decrement copy count
    game->decreaseCopies();

    // Prepend new borrow record to the list
    Node* newNode = new Node{ BorrowRecord(memberId, gameName), head };
    head = newNode;

    saveToCSV("data/borrows.csv");
    gameList.saveToCSV("data/games.csv");

    std::cout << "Borrowed successfully.\n";
    return true;
}

bool BorrowList::returnGame(const std::string& memberId,
                            const std::string& gameName,
                            GameList& gameList) {
    // Locate an active borrow for this member/game
    Node* node = findActiveBorrow(memberId, gameName);
    if (node == nullptr) {
        std::cout << "No active borrow found for this member/game.\n";
        return false;
    }

    // Mark as returned
    node->data.markReturned();

    // Restore the game copy count
    Game* game = gameList.searchGameByName(gameName);
    if (game != nullptr) {
        game->increaseCopies();
    }

	// Persist changes
	saveToCSV("data/borrows.csv");
	gameList.saveToCSV("data/games.csv");

    /*std::cout << "Returned successfully.\n";*/
    return true;
}

void BorrowList::displayMemberSummary(const std::string& memberId) const {
    // List all borrow records for the given member
    bool any = false;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.getMemberId() == memberId) {
            any = true;
            std::cout << "- " << curr->data.getGameName()
                      << " : " << (curr->data.isReturned() ? "Returned" : "Borrowed")
                      << "\n";
        }
        curr = curr->next;
    }
    if (!any) {
        std::cout << "No borrow records for this member.\n";
    }
}

// Admin function
void BorrowList::displayAllBorrowSummary() const {
    // List all borrow records (admin view)
    if (head == nullptr) {
        std::cout << "No borrow records.\n";
        return;
    }
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data.getMemberId() << " - "
                  << curr->data.getGameName() << " : "
                  << (curr->data.isReturned() ? "Returned" : "Borrowed")
                  << "\n";
        curr = curr->next;
    }
}

void BorrowList::addRecord(const BorrowRecord& record) {
    Node* newNode = new Node{ record, head };
    head = newNode;
}

void BorrowList::saveToCSV(const string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) return;

    file << "memberId,gameName,returned\n";

    Node* curr = head;
    while (curr != nullptr) {
        file << curr->data.getMemberId() << ","
            << curr->data.getGameName() << ","
            << (curr->data.isReturned() ? 1 : 0) << "\n";
        curr = curr->next;
    }

    file.close();
}