#include "MemberList.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

MemberList::MemberList() {
    for (int i = 0; i < MAX_MEMBERS; ++i)
        table[i] = nullptr;
}

MemberList::~MemberList() {
    for (int i = 0; i < MAX_MEMBERS; ++i) {
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
    return h % MAX_MEMBERS;
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

    displayAllMembers();
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

void MemberList::mergeSort(Member members[], int n) {
    mergeSort(members, 0, n - 1);
}

void MemberList::mergeSort(Member members[], int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        mergeSort(members, first, mid);
        mergeSort(members, mid + 1, last);
        merge(members, first, mid, last);
    }
}

void MemberList::merge(Member members[], int first, int mid, int last) {
    int left1 = first;
    int right1 = mid;
    int left2 = mid + 1;
    int right2 = last;
    int index = first;

    Member temp[MAX_MEMBERS];
    while (left1 <= right1 && left2 <= right2) {
        if (members[left1].getId() <= members[left2].getId()) {
            temp[index++] = members[left1++];
        }
        else {
            temp[index++] = members[left2++];
        }
    }
    while (left1 <= right1) {
        temp[index++] = members[left1++];
    }
    while (left2 <= right2) {
        temp[index++] = members[left2++];
    }
    for (int i = first; i <= last; i++) {
        members[i] = temp[i];
    }
}

void MemberList::displayAllMembers() const {
    cout << "===== Members List =====" << endl;
    Member members[MAX_MEMBERS];
    int count = 0;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        Node* curr = table[i];
        while (curr && count < MAX_MEMBERS) {
            members[count++] = curr->data;
            curr = curr->next;
        }
    }
    if (count == 0) {
        cout << "No members found.\n";
        return;
    }
    mergeSort(members, count);
    for (int i = 0; i < count; i++) {
        cout << members[i].getId() << " - " << members[i].getName() << endl;
    }
}

void MemberList::saveToCSV(const string& filename) const {
    Member members[MAX_MEMBERS];
    int count = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        Node* curr = table[i];
        while (curr && count < MAX_MEMBERS) {
            members[count++] = curr->data;
            curr = curr->next;
        }
    }
    if (count == 0) {
        return;
    }
    mergeSort(members, count);

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Enable to open file" << endl;
    }
    file << "memberId,name\n";
    for (int i = 0; i < count; i++) {
        file << members[i].getId() << "," << members[i].getName() << "\n";
    }
    file.close();
}
