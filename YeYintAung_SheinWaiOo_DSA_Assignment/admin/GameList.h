/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include<string>
#include <fstream>
#include<iostream>
#include "Game.h"
using namespace std;

typedef Game GameItem;

struct GameArray {
	Game** games;
	int size;
	int capacity;

	GameArray() : games(nullptr), size(0), capacity(0) {}
	~GameArray() { delete[] games; }

	void add(Game* game) {
		if (size >= capacity) {
			int newCapacity = (capacity == 0) ? 10 : capacity * 2;
			Game** newGames = new Game * [newCapacity];
			for (int i = 0; i < size; ++i) {
				newGames[i] = games[i];
			}
			delete[] games;
			games = newGames;
			capacity = newCapacity;
		}
		games[size++] = game;
	}

	void clear() {
		size = 0;
	}
};

class GameList
{
private:
	struct BinaryNode {
		GameItem item;
		BinaryNode* left;
		BinaryNode* right;
	};
	BinaryNode* root;

	BinaryNode* insert(BinaryNode* node, const Game& game);
	BinaryNode* search(BinaryNode* node, const string& gameName) const;
	BinaryNode* remove(BinaryNode* node, const string& gameName);
	void inorder(BinaryNode* node) const;
	void saveInOrder(BinaryNode* node, ofstream& file) const;
	void inorderCollect(BinaryNode* node, GameArray& games) const;
public:
	GameList();
	~GameList();

	void addGame();
	void removeGame();
	void insertGame(const Game& game);
	Game* searchGameByName(const string& gameName) const;
	void displayAllGames() const;
	void saveToCSV(const std::string& filename) const;
	void collectGames(GameArray& games) const;
};