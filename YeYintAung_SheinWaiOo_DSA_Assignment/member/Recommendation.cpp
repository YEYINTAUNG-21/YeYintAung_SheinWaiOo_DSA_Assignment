/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#include "Recommendation.h"

/*
Function: Recommendation
Description: Constructor that initializes the Recommendation system with a reference to the rating list.
Parameters:
- ratingL: Reference to the RatingList containing all user ratings.
Returns:
- None
*/
Recommendation::Recommendation(RatingList& ratingL) {
	ratingList = &ratingL;
}

/*
Function: containsMember
Description: Checks whether a member ID already exists in the given member list.
Parameters:
- members: Array of member IDs.
- size: Number of elements currently in the array.
- memberId: The member ID to check.
Returns:
- bool: True if the member ID exists, false otherwise.
*/
bool Recommendation::containsMember(string members[], int size, const string& memberId) const {
	for (int i = 0; i < size; i++) {
		if (members[i] == memberId) {
			return true;
		}
	}
	return false;
}


/*
Function: recommendGames
Description: Recommends games based on ratings from members who liked a target game.
Parameters:
- targetGameName: The name of the game used as the recommendation reference.
Returns:
- void
*/
void Recommendation::recommendGames(const string& targetGameName) {
	string likedMembers[MAX_MEMBERS];
	int likedCount = 0;

	// Find members who like the target game
	RatingList::Node* curr = ratingList->getHead();
	while (curr != nullptr) {
		if (curr->data.getGameName() == targetGameName && curr->data.getRating() >= LIKE_THRESHOLD) {
			if (!containsMember(likedMembers, likedCount, curr->data.getMemberId())) {
				likedMembers[likedCount++] = curr->data.getMemberId();
			}
		}
		curr = curr->next;
	}
	if (likedCount == 0) {
		cout << "No users rated this games with rating equal or more than " << LIKE_THRESHOLD << endl;
		return;
	}

	// Aggregate ratings for other games
	GameScore* score = new GameScore[MAX_GAMES]; 
	int scoreCount = 0;

	curr = ratingList->getHead();
	while (curr != nullptr) {
		if (containsMember(likedMembers, likedCount, curr->data.getMemberId()) && curr->data.getGameName() != targetGameName) {
			bool found = false;
			for (int i = 0; i < scoreCount; i++) {
				if (score[i].gameName == curr->data.getGameName()) {
					score[i].totalScore += curr->data.getRating();
					score[i].count++;
					found = true;
					break;
				}
			}
			if (!found) {
				score[scoreCount].gameName = curr->data.getGameName();
				score[scoreCount].totalScore = curr->data.getRating();
				score[scoreCount].count = 1;
				scoreCount++;
			}
		}
		curr = curr->next;
	}
	if (scoreCount == 0) {
		cout << "No recommendations available.\n";
		delete[] score;
		return;
	}

	// Calculate average rating
	for (int i = 0; i < scoreCount; i++) {
		score[i].average = (double)score[i].totalScore / score[i].count;
	}

	// Sorting
	mergeSort(score, scoreCount);

	// Display
	cout << "\nTop " << TOP_GAMES << " Recommended Games For You:\n";
	cout << "----------------------------------\n";

	int shown = 0;

	for (int i = 0; i < scoreCount && shown < TOP_GAMES; i++) {
		if (score[i].average >= LIKE_THRESHOLD) {
			cout << shown + 1 << ". "
				<< score[i].gameName
				<< " (Avg Rating: "
				<< score[i].average << ")" << endl;
			shown++;
		}
	}

	if (shown == 0) {
		cout << "No recommended games meet the rating threshold.\n";
	}
	cout << endl;
	delete[] score;
}

/*
Function: mergeSort
Description: Sorts an array of game scores using merge sort.
Parameters:
- scores: Array of GameScore objects.
- n: Number of elements in the array.
Returns:
- void
*/
void Recommendation::mergeSort(GameScore scores[], int n) {
	mergeSort(scores, 0, n - 1);
}

/*
Function: mergeSort
Description: Recursively divides the array and sorts game scores.
Parameters:
- scores: Array of GameScore objects.
- first: Starting index.
- last: Ending index.
Returns:
- void
*/
void Recommendation::mergeSort(GameScore scores[], int first, int last) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(scores, first, mid);
		mergeSort(scores, mid + 1, last);
		merge(scores, first, mid, last);
	}
}

/*
Function: merge
Description: Merges two sorted subarrays of game scores in descending order of average rating.
Parameters:
- scores: Array of GameScore objects.
- first: Starting index of the first subarray.
- mid: Ending index of the first subarray.
- last: Ending index of the second subarray.
Returns:
- void
*/
void Recommendation::merge(GameScore scores[], int first, int mid, int last) {
	int size = last - first + 1;
	GameScore* temp = new GameScore[size];
	int left1 = first;
	int right1 = mid;
	int left2 = mid + 1;
	int right2 = last;
	int index = 0;
	while (left1 <= right1 && left2 <= right2) {
		if (scores[left1].average > scores[left2].average) {
			temp[index++] = scores[left1++];
		}
		else {
			temp[index++] = scores[left2++];
		}
	}
	while (left1 <= right1) {
		temp[index++] = scores[left1++];
	}

	while (left2 <= right2) {
		temp[index++] = scores[left2++];
	}

	for (int i = 0; i < size; i++) {
		scores[first + i] = temp[i];
	}
	delete[] temp;
}