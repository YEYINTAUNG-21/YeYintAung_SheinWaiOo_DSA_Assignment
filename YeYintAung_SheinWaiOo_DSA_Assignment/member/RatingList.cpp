/*
Name: Shein Wai Oo
Group - 3
Student ID - S10269743C
*/
#include "RatingList.h"
#include <fstream>
#include <sstream>
#include <iomanip>

/*
Purpose: Get the head node (for recommendation).
Parameters: None.
Returns: Pointer to head node.
*/
RatingList::Node* RatingList::getHead() const { // need for recommendation
    return head;
}

/*
Purpose: Initialize an empty rating list.
Parameters: None.
Returns: None.
*/
RatingList::RatingList() : head(nullptr) {
}

/*
Purpose: Destroy the rating list and free all nodes.
Parameters: None.
Returns: None.
*/
RatingList::~RatingList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
    head = nullptr;
}

/*
Purpose: Find a review by member ID and game name.
Parameters:
- memberId: Member ID to match.
- gameName: Game name to match.
Returns: Pointer to matching node, or nullptr if not found.
*/
RatingList::Node* RatingList::findReview(const string& memberId, const string& gameName) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.getMemberId() == memberId &&
            curr->data.getGameName() == gameName) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

/*
Purpose: Add a rating record to the list.
Parameters:
- rating: Rating record to add.
Returns: None.
*/
void RatingList::addRecord(const Rating& rating) {
    Node* newNode = new Node{ rating, head };
    head = newNode;
}

/*
Purpose: Add or update a review for a game by a member.
Parameters:
- memberId: Member ID creating the review.
- memberList: Member list for validation.
- gameList: Game list for validation.
Returns: True if review saved, otherwise false.
*/
bool RatingList::addReview(const string& memberId, const MemberList& memberList, const GameList& gameList) {
    cout << "----------------------------------------\n";
    cout << "Rate a Game\n";
    cout << "----------------------------------------\n";

    if (!memberList.exists(memberId)) {
        cout << "Member not found.\n";
        return false;
    }

    string gameName;
    cout << "Enter Game Name: ";
    getline(cin, gameName);

    Game* game = gameList.searchGameByName(gameName);
    if (game == nullptr) {
        cout << "Game not found.\n";
        return false;
    }

    Node* existing = findReview(memberId, gameName);
    if (existing != nullptr) {
        cout << "Selected Game: " << gameName << "\n";
        cout << "You have already rated this game.\n\n";
        cout << "Your current rating and review:\n";
        cout << "--------------------------------\n";
        cout << "Rating : " << existing->data.getRating() << " / 10\n";
        string currentComment = existing->data.getComment();
        if (currentComment.empty()) {
            currentComment = "(no comment)";
        }
        cout << "Comment: " << currentComment << "\n";
        cout << "--------------------------------\n";
        cout << "Do you want to update your rating and review?\n";
        cout << "[1] Yes, update my review\n";
        cout << "[2] No, keep my existing review\n";
        int choice;
        //input validation
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter 1 or 2.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice == 1 || choice == 2) {
                break;
            }
			cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        if (choice != 1) {
            cout << "Your existing rating and review have been kept.\n";
            cout << "Returning to previous menu...\n";
            return false;
        }
    }

    int ratingValue;
    cout << "Enter Rating (1-10): ";
    cin >> ratingValue;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (ratingValue < 1 || ratingValue > 10) {
        cout << "Invalid rating. Please enter a value between 1 and 10.\n";
        return false;
    }

    string comment;
    cout << "Enter Review Comment: ";
    getline(cin, comment);

    if (existing != nullptr) {
        existing->data = Rating(memberId, gameName, ratingValue, comment);
        saveToCSV("data/reviews.csv");
		updateAverageRatings("data/averageRating.csv"); // Update average ratings after review update

        cout << "Your rating and review have been updated successfully.\n";
        cout << "Updated review:\n";
        cout << "--------------------------------\n";
        cout << "Rating : " << ratingValue << " / 10\n";
        cout << "Comment: " << (comment.empty() ? "(no comment)" : comment) << "\n";
        cout << "--------------------------------\n";
        return true;
    }

    addRecord(Rating(memberId, gameName, ratingValue, comment));
    saveToCSV("data/reviews.csv");
	updateAverageRatings("data/averageRating.csv"); // Update average ratings after new review

    cout << "Review submitted successfully.\n";
    return true;

}

/*
Purpose: Save ratings to CSV.
Parameters:
- filename: Output CSV path.
Returns: None.
*/
void RatingList::saveToCSV(const string& filename) const {
    ofstream file(filename, ios::out | ios::trunc);
    if (!file.is_open()) return;

    file << "memberId,gameName,rating,comment\n";

    Node* curr = head;
    while (curr != nullptr) {
        file << curr->data.getMemberId() << ","
             << curr->data.getGameName() << ","
             << curr->data.getRating() << ","
             << curr->data.getComment() << "\n";
        curr = curr->next;
    }

    file.close();
}

/*
Purpose: Recalculate and save average ratings to CSV.
Parameters:
- filename: Output CSV path.
Returns: None.
*/
void RatingList::updateAverageRatings(const string& filename) const {
    struct AvgNode {
        string gameName;
        int totalRating;
        int count;
        AvgNode* next;
    };

    AvgNode* avgHead = nullptr;

    Node* curr = head;
    while (curr != nullptr) {
        AvgNode* a = avgHead;
        while (a != nullptr && a->gameName != curr->data.getGameName()) {
            a = a->next;
        }
        if (a == nullptr) {
            avgHead = new AvgNode{ curr->data.getGameName(), 0, 0, avgHead };
            a = avgHead;
        }
        a->totalRating += curr->data.getRating();
        a->count += 1;

        curr = curr->next;
    }

    ofstream file(filename, ios::out | ios::trunc);
    if (!file.is_open()) return;

    file << "gameName,averageRating,totalReviews\n";

    AvgNode* a = avgHead;
    while (a != nullptr) {
        double avg = static_cast<double>(a->totalRating) / a->count;
        file << a->gameName << ","
            << fixed << setprecision(2) << avg << ","
            << a->count << "\n";
        a = a->next;
    }

    file.close();

    while (avgHead != nullptr) {
        AvgNode* toDelete = avgHead;
        avgHead = avgHead->next;
        delete toDelete;
    }
}

/*
Purpose: Get rating summary for a game.
Parameters:
- gameName: Game name to summarize.
- average: Output average rating.
- total: Output total review count.
Returns: None.
*/
void RatingList::getRatingSummary(const string& gameName, double& average, int& total) const {
    int sum = 0;
    total = 0;

    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.getGameName() == gameName) {
            sum += curr->data.getRating();
            total += 1;
        }
        curr = curr->next;
    }

    if (total > 0) {
        average = static_cast<double>(sum) / total;
    }
    else {
        average = 0.0;
    }
}

/*
Purpose: Display all reviews for a game.
Parameters:
- gameName: Game name whose reviews to display.
- memberList: Member list for reviewer names.
Returns: None.
*/
void RatingList::displayReviews(const string& gameName, const MemberList& memberList) const {
    bool any = false;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.getGameName() == gameName) {
            any = true;
            string name = memberList.getMemberName(curr->data.getMemberId());
            string comment = curr->data.getComment();
            if (comment.empty()) {
                comment = "(no comment)";
            }
            cout << "- " << name << ": \"" << comment << "\"\n";
        }
        curr = curr->next;
    }
    if (!any) {
        cout << "No reviews yet.\n";
    }
}