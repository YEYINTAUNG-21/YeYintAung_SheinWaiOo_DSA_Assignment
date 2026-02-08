/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#include "AdminList.h"

/*
Function: AdminList
Description: Default constructor that initializes an empty admin list.
Parameters:
- None
Returns:
- None
*/
AdminList::AdminList() : firstNode(nullptr), size(0) {
}

/*
Function: ~AdminList
Description: Destructor that deallocates all nodes in the admin linked list.
Parameters:
- None
Returns:
- None
*/
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

/*
Function: addAdmin
Description: Adds a new admin to the list if the admin ID does not already exist.
Parameters:
- id: The unique identifier for the admin.
- name: The name of the admin.
Returns:
- void
*/
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

/*
Function: login
Description: Checks whether an admin with the given ID exists in the list.
Parameters:
- adminId: The ID of the admin attempting to log in.
Returns:
- bool: True if the admin ID exists, false otherwise.
*/
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

/*
Function: getAdminName
Description: Retrieves the name of an admin based on the given admin ID.
Parameters:
- adminId: The ID of the admin.
Returns:
- string: The name of the admin if found, or an empty string if not found.
*/
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