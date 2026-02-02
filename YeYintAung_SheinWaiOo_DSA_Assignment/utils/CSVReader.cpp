#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

string trim(const string& s) {
    int start = 0;
    int end = (int)s.length() - 1;

    while (start <= end && isspace((unsigned char)s[start])) start++;
    while (end >= start && isspace((unsigned char)s[end])) end--;

    return s.substr(start, end - start + 1);
}

void CSVReader::loadGame(const string& filename, GameList& gameList) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open the file " << filename << endl;
        return;
    }

    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (count(line.begin(), line.end(), ',') < 5) continue;

        string name;
        int minPlayers, maxPlayers;
        int minPlayTime, maxPlayTime;
        int yearPublished;

        int index = 0;

        if (line[0] == '"') {
            int endQuote = line.find('"', 1);
            if (endQuote == string::npos) continue;
            name = line.substr(1, endQuote - 1);
            index = endQuote + 2;
        }
        else {
            int comma = line.find(',');
            if (comma == string::npos) continue;
            name = line.substr(0, comma);
            index = comma + 1;
        }

        name = trim(name);
        if (name.empty() || name.length() <= 1) continue; // ? removes "x"

        string data;

        data = trim(line.substr(index, line.find(',', index) - index));
        minPlayers = stoi(data);
        index = line.find(',', index) + 1;

        data = trim(line.substr(index, line.find(',', index) - index));
        maxPlayers = stoi(data);
        index = line.find(',', index) + 1;

        data = trim(line.substr(index, line.find(',', index) - index));
        minPlayTime = stoi(data);
        index = line.find(',', index) + 1;

        data = trim(line.substr(index, line.find(',', index) - index));
        maxPlayTime = stoi(data);
        index = line.find(',', index) + 1;

        data = trim(line.substr(index));
        yearPublished = stoi(data);

        Game game(name, minPlayers, maxPlayers,
            minPlayTime, maxPlayTime, yearPublished);

        gameList.insertGame(game);
    }

    file.close();
    cout << "Games loaded successfully from " << filename << endl;
}

void CSVReader::loadMember(const string& filename, MemberList& memberList) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        if (line.empty()) continue;

        string memberId, name;
        stringstream ss(line);

        getline(ss, memberId, ',');
        getline(ss, name);

        memberList.addMember(memberId, name);
    }

    file.close();
    cout << "Members loaded successfully from " << filename << endl;
}

void CSVReader::loadBorrow(const string& filename,
    BorrowList& borrowList,
    const MemberList& memberList,
    const GameList& gameList) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        if (line.empty()) continue;

        string memberId, gameName;
        int returned;

        stringstream ss(line);
        getline(ss, memberId, ',');
        getline(ss, gameName, ',');
        ss >> returned;

        BorrowRecord record(memberId, gameName);
        if (returned == 1) {
            record.markReturned();
        }

        borrowList.addRecord(record);
    }

    file.close();
    cout << "Borrow records loaded successfully from " << filename << endl;
}