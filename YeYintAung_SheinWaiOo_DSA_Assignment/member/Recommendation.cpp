#include "Recommendation.h"

Recommendation::Recommendation(RatingList& ratingL) {
	ratingList = &ratingL;
}

bool Recommendation::containsMember(string members[], int size, const string& memberId) const {
	for (int i = 0; i < size; i++) {
		if (members[i] == memberId) {
			return true;
		}
	}
	return false;
}

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
	GameScore score[MAX_GAMES];
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

	int limit = (scoreCount < TOP_GAMES) ? scoreCount : TOP_GAMES;
	for (int i = 0; i < limit; i++) {
		cout << i + 1 << ". "
			<< score[i].gameName
			<< " (Avg Rating: "
			<< score[i].average << ")" << endl;;
	}
	cout << endl;
}

void Recommendation::mergeSort(GameScore scores[], int n) {
	mergeSort(scores, 0, n - 1);
}

void Recommendation::mergeSort(GameScore scores[], int first, int last) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(scores, first, mid);
		mergeSort(scores, mid + 1, last);
		merge(scores, first, mid, last);
	}
}

void Recommendation::merge(GameScore scores[], int first, int mid, int last) {
	int size = last - first + 1;
	GameScore* temp = new GameScore[size];
	int left1 = first;
	int right1 = mid;
	int left2 = mid + 1;
	int right2 = last;
	int index = first;
	while (left1 <= right1 && left2 <= right2) {
		if (scores[left1].average > scores[left2].average) {
			temp[index++] = scores[left1++];
		}
		else {
			temp[index++] = scores[left2++];
		}
	}
	while (left1 <= right1)
		temp[index++] = scores[left1++];

	while (left2 <= right2)
		temp[index++] = scores[left2++];

	for (int i = first; i <= last; i++)
		scores[i] = temp[i];
}