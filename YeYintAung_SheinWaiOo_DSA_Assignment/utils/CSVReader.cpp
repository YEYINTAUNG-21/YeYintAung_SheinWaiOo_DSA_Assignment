#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

/*
Function: trim
Description: Removes leading and trailing whitespace from a string.
Parameters:
- s: The input string to be trimmed.
Returns:
- string: The trimmed string.
*/
string trim(const string& s) {
    int start = 0;
    int end = (int)s.length() - 1;

    while (start <= end && isspace((unsigned char)s[start])) start++;
    while (end >= start && isspace((unsigned char)s[end])) end--;

    return s.substr(start, end - start + 1);
}

/*
Function: loadGame
Description: Loads game data from a CSV file and inserts the games into the game list.
Parameters:
- filename: The name of the CSV file containing game data.
- gameList: Reference to the GameList to store loaded games.
Returns:
- void
*/
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
    //cout << "Games loaded successfully from " << filename << endl;
}

/*
Function: loadMember
Description: Loads member data from a CSV file and inserts members into the member list.
Parameters:
- filename: The name of the CSV file containing member data.
- memberList: Reference to the MemberList to store loaded members.
Returns:
- void
*/
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
    //cout << "Members loaded successfully from " << filename << endl;
}

/*
Function: loadBorrow
Description: Loads borrow records from a CSV file and adds them to the borrow list.
Parameters:
- filename: The name of the CSV file containing borrow records.
- borrowList: Reference to the BorrowList to store records.
- memberList: Reference to the MemberList (for validation context).
- gameList: Reference to the GameList (for validation context).
Returns:
- void
*/
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
    //cout << "Borrow records loaded successfully from " << filename << endl;
}

/*
Function: loadReview
Description: Loads game reviews and ratings from a CSV file into the rating list.
Parameters:
- filename: The name of the CSV file containing review data.
- ratingList: Reference to the RatingList to store loaded ratings.
Returns:
- void
*/
void CSVReader::loadReview(const string& filename, RatingList& ratingList) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open" << filename << endl;
        return;
    }

    string line;
    getline(file, line); // header

    while (getline(file, line)) {
        if (line.empty()) continue;

        string memberId, gameName, ratingStr, comment;
        stringstream ss(line);

        getline(ss, memberId, ',');
        getline(ss, gameName, ',');
        getline(ss, ratingStr, ',');
        getline(ss, comment);

        if (memberId.empty() || gameName.empty() || ratingStr.empty()) continue;

        int ratingValue = stoi(ratingStr);
        ratingList.addRecord(Rating(memberId, gameName, ratingValue, comment));
    }

    file.close();
    //cout << "Reviews loaded successfully from " << filename << endl;
}