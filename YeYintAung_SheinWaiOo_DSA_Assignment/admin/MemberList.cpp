/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#include "MemberList.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
Function: MemberList
Description: Default constructor that initializes the hash table with null pointers.
Parameters:
- None
Returns:
- None
*/
MemberList::MemberList() {
    for (int i = 0; i < MAX_MEMBERS; ++i)
        table[i] = nullptr;
}

/*
Function: ~MemberList
Description: Destructor that deallocates all nodes stored in the hash table.
Parameters:
- None
Returns:
- None
*/
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

/*
Function: hash
Description: Computes a hash index for a given member ID.
Parameters:
- memberId: The ID of the member.
Returns:
- int: Hash index within the table range.
*/
int MemberList::hash(const string& memberId) const {
    unsigned long h = 0;
    for (char c : memberId)
        h = h * 131 + c;
    return h % MAX_MEMBERS;
}

/*
Function: addMember
Description: Prompts the user to input member details and adds the member to the system.
Parameters:
- None
Returns:
- void
*/
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

/*
Function: addMember
Description: Adds a member with the given ID and name to the hash table.
Parameters:
- id: The unique identifier for the member.
- name: The name of the member.
Returns:
- void
*/
void MemberList::addMember(const string& id, const string& name) {
    if (exists(id)) return;

    int idx = hash(id);
    Node* newNode = new Node{ Member(id, name), table[idx] };
    table[idx] = newNode;
}

/*
Function: exists
Description: Checks whether a member with the given ID exists in the hash table.
Parameters:
- memberId: The ID of the member.
Returns:
- bool: True if the member exists, false otherwise.
*/
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

/*
Function: searchMemberById
Description: Searches for a member by ID in the hash table.
Parameters:
- id: The ID of the member to search for.
Returns:
- Member*: Pointer to the member if found, or nullptr if not found.
*/
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

/*
Function: getMemberName
Description: Retrieves the name of a member based on the member ID.
Parameters:
- memberId: The ID of the member.
Returns:
- string: The member name if found, otherwise "Unknown Member".
*/
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

/*
Function: mergeSort
Description: Sorts an array of members by their IDs using merge sort.
Parameters:
- members: Array of Member objects.
- n: Number of members in the array.
Returns:
- void
*/
void MemberList::mergeSort(Member members[], int n) {
    mergeSort(members, 0, n - 1);
}

/*
Function: mergeSort
Description: Recursively divides and sorts the member array.
Parameters:
- members: Array of Member objects.
- first: Starting index.
- last: Ending index.
Returns:
- void
*/
void MemberList::mergeSort(Member members[], int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        mergeSort(members, first, mid);
        mergeSort(members, mid + 1, last);
        merge(members, first, mid, last);
    }
}

/*
Function: merge
Description: Merges two sorted subarrays of members into a single sorted array.
Parameters:
- members: Array of Member objects.
- first: Starting index of the first subarray.
- mid: Ending index of the first subarray.
- last: Ending index of the second subarray.
Returns:
- void
*/
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

/*
Function: displayAllMembers
Description: Displays all members sorted by member ID.
Parameters:
- None
Returns:
- void
*/
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

/*
Function: saveToCSV
Description: Saves all members to a CSV file in sorted order.
Parameters:
- filename: The name of the CSV file.
Returns:
- void
*/
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
