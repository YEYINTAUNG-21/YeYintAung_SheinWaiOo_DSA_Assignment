#include <iostream>
#include "admin/AdminList.h"
#include "admin/GameList.h"
#include "admin/MemberList.h"
#include "member/BorrowList.h"
#include "utils/CSVReader.h"
using namespace std;

void adminMenu(GameList& gameList, MemberList& memberList, BorrowList& borrowList, AdminList& adminList, const string& adminId) {
    cout << "Welcome, " << adminList.getAdminName(adminId) << "!\n";
    int choice;
    do {
        cout << "--- Administrator Menu ---\n";
        cout << "1. Add a new board game\n";
        cout << "2. Remove a board game\n";
        cout << "3. Add a new member\n";
        cout << "4. Display a summary of games borrowed/returned\n";
        cout << "0. Logout\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            gameList.addGame();
            break;
        }

        case 2: {
            gameList.removeGame();
            break;
        }

        case 3: {
            memberList.addMember();
            break;
        }

        case 4: {
            borrowList.displayAllBorrowSummary();
            break;
        }

        case 0: {
            cout << "Admin logged out.\n";
            break;
        }

        default: {
            cout << "Invalid choice.\n";
        }
        }
    } while (choice != 0);
}

void memberMenu(GameList& gameList, BorrowList& borrowList, MemberList& memberList, const string& memberId) {
    cout << "Welcome, " << memberList.getMemberName(memberId) << "!\n";
    int choice;
    do {
        cout << "--- Member Menu ---\n";
        cout << "1. Borrow a board game\n";
        cout << "2. Return a board game\n";
        cout << "3. Display my borrow/return summary\n";
        cout << "0. Back\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            borrowList.borrowGame(memberId, gameName, gameList);
            break;
        }

        case 2: {
            borrowList.returnGame(memberId, gameName);
            break;
        }

        case 3: {
            borrowList.displayMemberSummary(memberId);
            break;
        }


        case 0: {
            cout << "Member logged out.\n";
            break;
        }

        default: {
            cout << "Invalid choice.\n";
        }
        }
    } while (choice != 0);
}

int main()
{
    GameList gameList;
    MemberList memberList;
    BorrowList borrowList;
    AdminList adminList;

    adminList.addAdmin("A100", "YYA");
    adminList.addAdmin("A200", "SWO");

    CSVReader::loadGame("games.csv", gameList);
    
    int choice;
    do {
        cout << "--- Board Game System ---\n";
        cout << "1. Admin Login\n";
        cout << "2. Member Login\n";
        cout << "3. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string adminId;
            cout << "Enter Admin ID: ";
            cin >> adminId;
            if (adminList.login(adminId)) {
                cout << "Admin login successful.\n";
                adminMenu(gameList, memberList, borrowList, adminList, adminId);
            }
            else {
                cout << "Invalid Admin ID.\n";
            }
            break;
        }

        case 2: {
            string memberId;
            cout << "Enter Member ID: ";
            cin >> memberId;
            if (memberList.exists(memberId)) {
                cout << "Member login successful.\n";
                memberMenu(gameList, borrowList, memberList, memberId);
            }
            else {
                cout << "Member not found.\n";
            }
            break;
        }

        case 0: {
            cout << "Exiting system...\n";
            break;
        }

        default: {
            cout << "Invalid choice.\n";
        }
        }
    } while (choice != 0);
}