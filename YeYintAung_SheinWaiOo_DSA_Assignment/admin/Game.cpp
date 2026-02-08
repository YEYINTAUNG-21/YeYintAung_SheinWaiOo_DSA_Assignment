/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#include "Game.h"

/*
Function: Game
Description: Default constructor that initializes a game with empty name and zero values for all attributes.
Parameters:
- None
Returns:
- None
*/
Game::Game() {
	gameName = "";
	minPlayers = maxPlayers = 0;
	minPlayTime = maxPlayTime = 0;
	yearPublished = 0;
	copies = 1;
}

/*
Function: Game
Description: Parameterized constructor that initializes a game with the given details.
Parameters:
- name: The name of the game.
- minP: Minimum number of players.
- maxP: Maximum number of players.
- minT: Minimum play time in minutes.
- maxT: Maximum play time in minutes.
- year: Year the game was published.
Returns:
- None
*/
Game::Game(const string& name, int minP, int maxP, int minT, int maxT, int year) {
	gameName = name;
	minPlayers = minP;
	maxPlayers = maxP;
	minPlayTime = minT;
	maxPlayTime = maxT;
	yearPublished = year;
	copies = 1;
}

/*
Function: getName
Description: Retrieves the name of the game.
Parameters:
- None
Returns:
- string: The name of the game.
*/
string Game::getName() const {
	return gameName;
}

/*
Function: getMinPlayer
Description: Retrieves the minimum number of players required to play the game.
Parameters:
- None
Returns:
- int: Minimum number of players.
*/
int Game::getMinPlayer() const {
	return minPlayers;
}

/*
Function: getMaxPlayer
Description: Retrieves the maximum number of players allowed to play the game.
Parameters:
- None
Returns:
- int: Maximum number of players.
*/
int Game::getMaxPlayer() const {
	return maxPlayers;
}

/*
Function: getMinPlayTime
Description: Retrieves the minimum play time of the game in minutes.
Parameters:
- None
Returns:
- int: Minimum play time.
*/
int Game::getMinPlayTime() const {
	return minPlayTime;
}

/*
Function: getMaxPlayTime
Description: Retrieves the maximum play time of the game in minutes.
Parameters:
- None
Returns:
- int: Maximum play time.
*/
int Game::getMaxPlayTime() const {
	return maxPlayTime;
}

/*
Function: getYearPublished
Description: Retrieves the year the game was published.
Parameters:
- None
Returns:
- int: Year of publication.
*/
int Game::getYearPublished() const {
	return yearPublished;
}

/*
Function: getCopies
Description: Retrieves the number of available copies of the game.
Parameters:
- None
Returns:
- int: Number of copies.
*/
int Game::getCopies() const {
	return copies;
}

/*
Function: increaseCopies
Description: Increases the number of available copies of the game by one.
Parameters:
- None
Returns:
- void
*/
void Game::increaseCopies() {
	copies++;
}

/*
Function: decreaseCopies
Description: Decreases the number of available copies of the game by one if copies are available.
Parameters:
- None
Returns:
- bool: True if a copy was successfully decreased, false if no copies were available.
*/
bool Game::decreaseCopies() {
	if (copies > 0) {
		copies--;
		return true;
	}
	return false;
}