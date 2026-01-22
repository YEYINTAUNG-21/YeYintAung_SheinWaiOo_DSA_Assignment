#include "Game.h"

Game::Game() {
	gameName = "";
	minPlayers = maxPlayers = 0;
	minPlayTime = maxPlayTime = 0;
	yearPublished = 0;
	copies = 1;
}

Game::Game(const string& name, int minP, int maxP, int minT, int maxT, int year) {
	gameName = name;
	minPlayers = minP;
	maxPlayers = maxP;
	minPlayTime = minT;
	maxPlayTime = maxT;
	yearPublished = year;
	copies = 1;
}

string Game::getName() const {
	return gameName;
}

int Game::getCopies() const {
	return copies;
}

void Game::increaseCopies() {
	copies++;
}

bool Game::decreaseCopies() {
	if (copies > 0) {
		copies--;
		return true;
	}
	return false;
}