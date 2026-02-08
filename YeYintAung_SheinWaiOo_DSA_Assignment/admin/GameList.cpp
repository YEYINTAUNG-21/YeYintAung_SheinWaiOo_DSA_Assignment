#include "GameList.h"
#include<string>
#include <fstream>
#include<iostream>
using namespace std;

GameList::GameList() {
	root = nullptr;
}

GameList::~GameList() {
    while (root != nullptr) {
        root = remove(root, root->item.getName());
    }
}

void GameList::addGame() {
    string name;
    int minP, maxP, minT, maxT, year;

    cout << "Enter game name: ";
    getline(cin, name);
    Game* existing = searchGameByName(name);
    if (existing != nullptr) {
        cout << "Game already exists with "
            << existing->getCopies() << " copies.\n";
        cout << "How many copies do you want to add? (0 to cancel): ";

        int add;
        cin >> add;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (add > 0) {
            for (int i = 0; i < add; i++) {
                existing->increaseCopies();
            }
            cout << "Copies updated. Total copies: "
                << existing->getCopies() << endl;
            saveToCSV("data/games.csv");
        }
        else {
            cout << "No copies added.\n";
        }
        return;
    }
    cout << "Enter minimum player: ";
    cin >> minP;
    cout << "Enter maximum player: ";
    cin >> maxP;
    cout << "Enter minimum play time(min): ";
    cin >> minT;
    cout << "Enter maximum play time(min): ";
    cin >> maxT;
    cout << "Enter year published: ";
    cin >> year;

    Game game(name, minP, maxP, minT, maxT, year);
    insertGame(game);
    displayAllGames();
    cout << "Game added successfully" << endl;
    saveToCSV("data/games.csv");
}

void GameList::removeGame() {
    displayAllGames();
    string name;
    cout << "Enter game name to remove: ";
    getline(cin, name);

    Game* game = searchGameByName(name);
    if (game == nullptr) {
        cout << "Game not found.\n";
        return;
    }

    int copies = game->getCopies();
    if (copies > 1) {
        cout << "Game has " << copies << " copies.\n";
        cout << "How many copies do you want to delete? (0 to cancel): ";

        int del;
        cin >> del;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (del <= 0) {
            cout << "Deletion cancelled.\n";
            return;
        }

        if (del >= copies) {
            root = remove(root, name);
            cout << "All copies removed. Game deleted.\n";
        }
        else {
            for (int i = 0; i < del; i++) {
                game->decreaseCopies();
            }
            cout << "Copies remaining: "
                << game->getCopies() << endl;
        }
    }
    else {
        root = remove(root, name);
        displayAllGames();
        cout << "Game removed successfully.\n";
    }
    saveToCSV("data/games.csv");
}


GameList::BinaryNode* GameList::remove(BinaryNode* node, const string& gameName) {
    if (node == nullptr) {
        return nullptr;
    }
    if (gameName < node->item.getName()) {
        node->left = remove(node->left, gameName);
    }
    else if (gameName > node->item.getName()) {
        node->right = remove(node->right, gameName);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {
            BinaryNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            BinaryNode* temp = node->left;
            delete node;
            return temp;
        }
        else {
            BinaryNode* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            node->item = successor->item;
            node->right = remove(node->right, successor->item.getName());
        }
    }
    return node;
}

void GameList::insertGame(const Game& game) {
	root = insert(root, game);
}

GameList::BinaryNode* GameList::insert(BinaryNode* node, const Game& game) {
    if (node == nullptr) {
        BinaryNode* newNode = new BinaryNode;
        newNode->item = game;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (game.getName() < node->item.getName()) {
        node->left = insert(node->left, game);
    }
    else if (game.getName() > node->item.getName()) {
        node->right = insert(node->right, game);
    }
    else {
        node->item.increaseCopies();
    }
    return node;
}

Game* GameList::searchGameByName(const string& gameName) const {
    BinaryNode* node = search(root, gameName);
    if (node == nullptr) {
        return nullptr;
    }
    return &(node->item);
}

GameList::BinaryNode* GameList::search(BinaryNode* node, const string& gameName) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (gameName == node->item.getName()) {
        return node;
    }
    else if (gameName < node->item.getName()) {
        return search(node->left, gameName);
    }
    else {
        return search(node->right, gameName);
    }
}

void GameList::displayAllGames() const{
	inorder(root);
}

// Modified inorder to only show available games
void GameList::inorder(BinaryNode * node) const {
    if (node == nullptr) {
        return;
    }

    inorder(node->left);

    int copies = node->item.getCopies();
    if (copies > 0) { // only show games that are currently available
        cout << node->item.getName();
        if (copies > 1) {
            cout << " (Copies: " << copies << ")";
        }
        cout << endl;
    }

    inorder(node->right);
}

void GameList::saveInOrder(BinaryNode* node, ofstream& file) const {
    if (!node) return;

    saveInOrder(node->left, file);

    Game& g = node->item;
    for (int i = 0; i < g.getCopies(); i++) {
        file << "\"" << g.getName() << "\"" << ","
            << g.getMinPlayer() << ","
            << g.getMaxPlayer() << ","
            << g.getMinPlayTime() << ","
            << g.getMaxPlayTime() << ","
            << g.getYearPublished() << "\n";
    }

    saveInOrder(node->right, file);
}

void GameList::saveToCSV(const std::string& filename) const {
    std::ofstream file(filename, ios::out | ios::trunc);
    if (!file.is_open()) return;

    file << "name,minPlayers,maxPlayers,minTime,maxTime,year\n";
    saveInOrder(root, file);
    file.close();
}

void GameList::inorderCollect(BinaryNode* node, GameArray& games) const {
    if (node == nullptr) {
        return;
    }

    inorderCollect(node->left, games);
    games.add(&node->item);
    inorderCollect(node->right, games);
}

void GameList::collectGames(GameArray& games) const {
    games.clear();
    inorderCollect(root, games);
}