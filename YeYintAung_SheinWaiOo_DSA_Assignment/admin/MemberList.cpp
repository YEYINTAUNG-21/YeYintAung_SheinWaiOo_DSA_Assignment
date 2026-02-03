#include "MemberList.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

MemberList::MemberList() {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table[i] = nullptr;
}

MemberList::~MemberList() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* curr = table[i];
        while (curr != nullptr) {
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
    }
}

int MemberList::hash(const string& memberId) const {
    unsigned long h = 0;
    for (char c : memberId)
        h = h * 131 + c;
    return h % TABLE_SIZE;
}

void MemberList::addMember() {
    string id, name;

    cout << "Enter Member ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (exists(id)) {
        cout << "Member already exists.\n";
        return;
    }

    cout << "Enter Member Name: ";
    getline(cin, name);

    addMember(id, name);
    saveToCSV("data/members.csv");

    cout << "Member added successfully.\n";
}

void MemberList::addMember(const string& id, const string& name) {
    if (exists(id)) return;

    int idx = hash(id);
    Node* newNode = new Node{ Member(id, name), table[idx] };
    table[idx] = newNode;
}

bool MemberList::exists(const string& memberId) const {
    int idx = hash(memberId);
    Node* curr = table[idx];
    while (curr) {
        if (curr->data.getId() == memberId)
            return true;
        curr = curr->next;
    }
    return false;
}

Member* MemberList::searchMemberById(const string& id) {
    int idx = hash(id);
    Node* curr = table[idx];
    while (curr) {
        if (curr->data.getId() == id)
            return &curr->data;
        curr = curr->next;
    }
    return nullptr;
}

string MemberList::getMemberName(const string& memberId) const {
    int idx = hash(memberId);
    Node* curr = table[idx];
    while (curr) {
        if (curr->data.getId() == memberId)
            return curr->data.getName();
        curr = curr->next;
    }
    return "Unknown Member";
}

void MemberList::displayAllMembers() const {
    bool empty = true;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* curr = table[i];
        while (curr) {
            empty = false;
            cout << curr->data.getId()
                << " - "
                << curr->data.getName()
                << endl;
            curr = curr->next;
        }
    }
    if (empty)
        cout << "No members found.\n";
}

// ===== LOAD CSV =====
//void MemberList::loadFromCSV(const string& filename) {
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cout << "Unable to open " << filename << endl;
//        return;
//    }
//
//    string line;
//    getline(file, line); // header
//
//    while (getline(file, line)) {
//        if (line.empty()) continue;
//
//        int comma = line.find(',');
//        if (comma == string::npos) continue;
//
//        string id = line.substr(0, comma);
//        string name = line.substr(comma + 1);
//
//        addMember(id, name);
//    }
//
//    file.close();
//    cout << "Members loaded successfully from " << filename << endl;
//}

void MemberList::saveToCSV(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) return;

    file << "memberId,name\n";

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* curr = table[i];
        while (curr) {
            file << curr->data.getId() << ","
                << curr->data.getName() << "\n";
            curr = curr->next;
        }
    }
    file.close();
}

