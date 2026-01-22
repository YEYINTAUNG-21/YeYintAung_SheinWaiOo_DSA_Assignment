/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#pragma once
#include<string>
#include<iostream>
#include "Game.h"
using namespace std;

typedef Game GameItem;

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

public:
	GameList();
	~GameList();

	void addGame();                       
	void removeGame();                    
	void insertGame(const Game& game);
	Game* searchGameByName(const string& gameName) const;
	void displayAllGames() const;
};