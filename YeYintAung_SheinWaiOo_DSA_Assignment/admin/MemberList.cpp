//#include "MemberList.h"
//
//MemberList::MemberList() {}

//Shein-Tested For Temporary Completion
#include "MemberList.h"
#include <limits>

MemberList::MemberList() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

MemberList::~MemberList() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* curr = table[i];
        while (curr != nullptr) {
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        table[i] = nullptr;
    }
}

int MemberList::hash(const string& memberId) const {
    unsigned long h = 0;
    for (char c : memberId) {
        h = h * 131 + static_cast<unsigned long>(c);
    }
    return static_cast<int>(h % TABLE_SIZE);
}

void MemberList::addMember() {
    string id;
    string name;

    cout << "Enter Member ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Member Name: ";
    getline(cin, name);

    if (exists(id)) {
        cout << "Member already exists.\n";
        return;
    }

    addMember(id, name);
    cout << "Member added successfully.\n";
}

void MemberList::addMember(const string& id, const string& name) {
    if (exists(id)) {
        return; // silently ignore duplicates in programmatic add
    }

    int idx = hash(id);
    Node* newNode = new Node{ Member(id, name), table[idx] };
    table[idx] = newNode;
}

bool MemberList::exists(const string& memberId) const {
    int idx = hash(memberId);
    Node* curr = table[idx];
    while (curr != nullptr) {
        if (curr->data.getId() == memberId) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

string MemberList::getMemberName(const string& memberId) const {
    int idx = hash(memberId);
    Node* curr = table[idx];
    while (curr != nullptr) {
        if (curr->data.getId() == memberId) {
            return curr->data.getName();
        }
        curr = curr->next;
    }
    return "";
}