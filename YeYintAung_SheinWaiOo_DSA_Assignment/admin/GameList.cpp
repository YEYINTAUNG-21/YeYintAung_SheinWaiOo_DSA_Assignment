#include "GameList.h"

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
    cout << "Enter minimum player: ";
    cin >> minP;
    cout << "Enter maximum player: ";
    cin >> maxP;
    cout << "Enter minimum play time(min): ";
    cin >> minT;
    cout << "Enter maximum play time(min): ";
    cin >> maxT;
    cout << "Enter year published(min): ";
    cin >> year;

    Game game(name, minP, maxP, minT, maxT, year);
    insertGame(game);
    cout << "Game added successfully" << endl;
}

void GameList::removeGame() {
    string name;
    cout << "Enter game name to remove: " << flush;
    getline(cin, name);

    Game* game = searchGameByName(name);
    if (game == nullptr) {
        cout << "Game not found" << endl;
        return;
    }
    if (game->getCopies() > 1) {
        game->decreaseCopies();
        cout << "One copy removed. Remaining copies: " << game->getCopies() << endl;
    }
    else {
        root = remove(root, name);
        cout << "Game removed successfully" << endl;
    }
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


//void GameList::inorder(BinaryNode* node) const {
//	if (node == nullptr) {
//		return;
//	}
//	else {
//		inorder(node->left);
//        cout << node->item.getName();
//        if (node->item.getCopies() > 1) {
//            cout << " (Copies: " << node->item.getCopies() << ")";
//        }
//        cout << endl;
//		inorder(node->right);
//	}
//}

//Shein-Tested: Modified inorder to only show available games
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