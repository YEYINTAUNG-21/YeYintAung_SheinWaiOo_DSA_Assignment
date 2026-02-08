#include <iostream>
#include <limits>
#include <iomanip>
#include "admin/AdminList.h"
#include "admin/GameList.h"
#include "admin/MemberList.h"
#include "member/BorrowList.h"
#include "utils/CSVReader.h"
#include "member/RatingList.h"
#include "member/Recommendation.h"
using namespace std;

/*
Purpose: Display the admin menu and route admin actions.
Parameters:
- gameList: Game list for managing inventory.
- memberList: Member list for managing members.
- borrowList: Borrow list for admin summaries.
- adminList: Admin list for account info.
- adminId: Logged-in admin ID.
Returns: None.
*/
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

/*
Purpose: Display a selected game's details and ratings.
Parameters:
- gameList: Game list for game lookup.
- ratingList: Rating list for summary and reviews.
- memberList: Member list for reviewer names.
Returns: None.
*/
void viewGameDetails(GameList& gameList, RatingList& ratingList, MemberList& memberList) {
    string gameName;

    gameList.displayAllGames();
    cout << "Enter game name to view details: ";
    getline(cin, gameName);

    Game* game = gameList.searchGameByName(gameName);
    if (game == nullptr) {
        cout << "Game not found.\n";
        return;
    }

    double average = 0.0;
    int total = 0;
    ratingList.getRatingSummary(gameName, average, total);

    cout << "========================================\n";
    cout << "            GAME DETAILS\n";
    cout << "========================================\n";
    cout << "Title            : " << game->getName() << "\n";
    cout << "Players          : " << game->getMinPlayer() << " - " << game->getMaxPlayer() << " players\n";
    cout << "Play Time        : " << game->getMinPlayTime() << " - " << game->getMaxPlayTime() << " minutes\n";
    cout << "Year             : " << game->getYearPublished() << "\n";
    cout << "Available Copies : " << game->getCopies() << "\n\n";

    cout << "----------------------------------------\n";
    cout << "Rating Summary\n";
    cout << "----------------------------------------\n";
    if (total > 0) {
        cout << "Average Rating   : " << fixed << setprecision(2) << average << " / 10\n";
    }
    else {
        cout << "Average Rating   : Not available\n";
    }
    cout << "Total Reviews    : " << total << "\n\n";

    cout << "----------------------------------------\n";
    cout << "User Reviews\n";
    cout << "----------------------------------------\n";
    ratingList.displayReviews(gameName, memberList);
    cout << "========================================\n";
}

/*
Purpose: Display games filtered by player count and sorted by criteria.
Parameters:
- gameList: Game list for collecting games.
- ratingList: Rating list for average ratings.
Returns: None.
*/
void displayGamesByPlayers(GameList& gameList, RatingList& ratingList) {
    cout << "----------------------------------------\n";
    cout << "Filter Games by Player Count\n";
    cout << "----------------------------------------\n";

    int players;
    while (true) {
        cout << "Enter number of players: ";
        cin >> players;
        if (cin.fail() || players <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "How would you like the list to be sorted?\n";
    cout << "[1] Year of publication (newest first)\n";
    cout << "[2] Year of publication (oldest first)\n";
    cout << "[3] Average rating (highest first)\n";
    cout << "[4] Average rating (lowest first)\n";

    int choice;
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1 to 4.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice >= 1 && choice <= 4) {
            break;
        }
        cout << "Invalid choice. Please enter 1 to 4.\n";
    }

    GameArray gameArray;
    gameList.collectGames(gameArray);

    struct GameView {
        Game* game;
        double average;
        int total;
    };

    GameView* filtered = new GameView[gameArray.size];
    int filteredCount = 0;

    for (int i = 0; i < gameArray.size; ++i) {
        Game* g = gameArray.games[i];
        if (g->getCopies() <= 0) {
            continue;
        }
        if (players >= g->getMinPlayer() && players <= g->getMaxPlayer()) {
            double avg = 0.0;
            int total = 0;
            ratingList.getRatingSummary(g->getName(), avg, total);
            filtered[filteredCount++] = GameView{ g, avg, total };
        }
    }


    if (filteredCount == 0) {
        cout << "No games found for " << players << " players.\n";
        delete[] filtered;
        return;
    }

    auto avgForDesc = [](const GameView& v) {
        return (v.total == 0) ? -1.0 : v.average;
        };
    auto avgForAsc = [](const GameView& v) {
        return (v.total == 0) ? 11.0 : v.average;
        };

    // Manual bubble sort
    for (int i = 0; i < filteredCount - 1; ++i) {
        for (int j = 0; j < filteredCount - i - 1; ++j) {
            bool swap = false;
            switch (choice) {
            case 1:
                swap = (filtered[j].game->getYearPublished() < filtered[j + 1].game->getYearPublished());
                break;
            case 2:
                swap = (filtered[j].game->getYearPublished() > filtered[j + 1].game->getYearPublished());
                break;
            case 3:
                swap = (avgForDesc(filtered[j]) < avgForDesc(filtered[j + 1]));
                break;
            case 4:
                swap = (avgForAsc(filtered[j]) > avgForAsc(filtered[j + 1]));
                break;
            }
            if (swap) {
                GameView temp = filtered[j];
                filtered[j] = filtered[j + 1];
                filtered[j + 1] = temp;
            }
        }
    }

    cout << "========================================\n";
    cout << "Games playable by " << players << " players\n";
    cout << "========================================\n";

    cout << "========================================\n";
    cout << "Games playable by " << players << " players\n";
    cout << "========================================\n";

    for (int i = 0; i < filteredCount; ++i) {
        const GameView& v = filtered[i];
        cout << "[" << (i + 1) << "] " << v.game->getName()
            << " (" << v.game->getYearPublished() << ")\n";
        cout << "  Players         : " << v.game->getMinPlayer() << " - "
            << v.game->getMaxPlayer() << "\n";
        if (v.total > 0) {
            cout << "  Avg Rating      : " << fixed << setprecision(2)
                << v.average << " / 10\n";
        }
        else {
            cout << "  Avg Rating      : Not rated yet\n";
        }
        cout << "  Available Copies: " << v.game->getCopies() << "\n\n";
    }

    cout << "Total games found: " << filteredCount << "\n";
    cout << "========================================\n";

    delete[] filtered;
}

/*
Purpose: Display and handle the member menu flow.
Parameters:
- gameList: Game list for member operations.
- borrowList: Borrow list for borrow/return operations.
- memberList: Member list for validation and names.
- ratingList: Rating list for reviews.
- memberId: Logged-in member ID.
Returns: None.
*/
void memberMenu(GameList& gameList, BorrowList& borrowList, MemberList& memberList, RatingList& ratingList, const string& memberId) {
    cout << "Welcome, " << memberList.getMemberName(memberId) << "!\n";
    int choice;
    do {
        cout << "1. Borrow a board game\n";
        cout << "2. Return a board game\n";
        cout << "3. Display my borrow/return summary\n";
        cout << "4. View game details\n";
        cout << "5. Filter games by player count\n";
		cout << "6. Rate and review a board game\n";
        cout << "7. Get game recommendations\n";
        cout << "0. Back\n";
        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1: {
            string gameName;
            // STEP 1: Display all available games to the logged-in member
			gameList.displayAllGames();
            
            // STEP 2: Prompt member to enter the game name they want to borrow
            cout << "Enter game name to borrow: ";
			getline(cin, gameName);
            
            // STEP 3: Attempt to borrow the selected game
            // - Validates member existence
            // - Checks game availability
            // - Records the borrow in a linked list
            // - Updates game inventory
            if (borrowList.borrowGame(memberId, gameName, memberList, gameList)) {
                // STEP 4: Display updated game list after successful borrow
                gameList.displayAllGames();
				cout << "Borrowed successfully.\n";
            }
            break;
        }

        case 2: {

            // STEP 1: Display all active (not yet returned) borrow records
            // for the logged-in member to guide the return process
            string gameName;
			borrowList.displayActiveBorrows(memberId);

            // STEP 2: Prompt the member to enter the game name to return
			cout << "Enter game name to return: ";
			getline(cin, gameName);
            
            //STEP 3: Attempt to return the specified game
            // - Searches for an active borrow record in the linked list
            // - Marks the borrow as returned
            // - Restores the game's available copy count
            if (borrowList.returnGame(memberId, gameName, gameList)) {
                gameList.displayAllGames();
				cout << "Returned successfully.\n";
            }
            break;
        }

        case 3: {
            borrowList.displayMemberSummary(memberId);
            break;
        }

        case 4: {
            viewGameDetails(gameList, ratingList, memberList);
            break;
		}

        case 5: {
            displayGamesByPlayers(gameList, ratingList);
            break;
        }

        case 6: {
            if (ratingList.addReview(memberId, memberList, gameList)) {
            }
            break;
        }

        case 7: {
            string gameName;

            gameList.displayAllGames();
            cout << "Enter a game you like: ";
            getline(cin, gameName);

            if (gameList.searchGameByName(gameName) == nullptr) {
                cout << "Game not found. Please enter a valid game name.\n";
                break;
            }

            Recommendation recommender(ratingList);
            recommender.recommendGames(gameName);
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

/*
Purpose: Application entry point. Loads data and handles login flow.
Parameters: None.
Returns: Exit code (0 on normal completion).
*/
int main()
{
    GameList gameList;
    MemberList memberList;
    BorrowList borrowList;
    AdminList adminList;
	RatingList ratingList;

    adminList.addAdmin("A100", "YYA");
    adminList.addAdmin("A200", "SWO");

    CSVReader::loadGame("data/games.csv", gameList);
    CSVReader::loadMember("data/members.csv", memberList);
    CSVReader::loadBorrow("data/borrows.csv", borrowList, memberList, gameList);
    CSVReader::loadReview("data/reviews.csv", ratingList);
    
    int choice;
    do {
        cout << "--- Board Game System ---\n";
        cout << "1. Admin Login\n";
        cout << "2. Member Login\n";
        cout << "0. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            string adminId;
            cout << "Enter Admin ID: ";
            cin >> adminId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (memberList.exists(memberId)) {
                cout << "Member login successful.\n";
                memberMenu(gameList, borrowList, memberList, ratingList, memberId);
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

