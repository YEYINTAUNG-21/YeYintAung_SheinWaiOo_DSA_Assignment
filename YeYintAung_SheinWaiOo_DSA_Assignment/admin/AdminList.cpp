//#include "AdminList.h"
//
//AdminList::AdminList() {}

//Shein-Tested For Temporary Completion
#include "AdminList.h"

AdminList::AdminList() : firstNode(nullptr), size(0) {
}

AdminList::~AdminList() {
    Node* curr = firstNode;
    while (curr != nullptr) {
        Node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
    firstNode = nullptr;
    size = 0;
}

void AdminList::addAdmin(const string& id, const string& name) {
    // prevent duplicate IDs
    Node* curr = firstNode;
    while (curr != nullptr) {
        if (curr->item.getId() == id) {
            return;
        }
        curr = curr->next;
    }
    Node* newNode = new Node{ AdminItem(id, name), firstNode };
    firstNode = newNode;
    ++size;
}

bool AdminList::login(const string& adminId) const {
    Node* curr = firstNode;
    while (curr != nullptr) {
        if (curr->item.getId() == adminId) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

string AdminList::getAdminName(const string& adminId) const {
    Node* curr = firstNode;
    while (curr != nullptr) {
        if (curr->item.getId() == adminId) {
            return curr->item.getName();
        }
        curr = curr->next;
    }
    return "";
}