#include "GameList.h"

GameList::GameList() {
	root = nullptr;
}

GameList::~GameList() {

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


void GameList::displayAllGames() const{
	inorder(root);
}

void GameList::inorder(BinaryNode* node) const {
	if (node == nullptr) {
		return;
	}
	else {
		inorder(node->left);
        cout << node->item.getName();
        if (node->item.getCopies() > 1) {
            cout << " (Copies: " << node->item.getCopies() << ")";
        }
        cout << endl;
		inorder(node->right);
	}
}