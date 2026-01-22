#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

string trim(const string& s) {
    int start = 0;
    int end = s.length() - 1;

    while (start <= end && isspace(s[start])) start++;
    while (end >= start && isspace(s[end])) end--;

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

        string name;
        int minPlayers, maxPlayers;
        int minPlayTime, maxPlayTime;
        int yearPublished;

        int index = 0;

        if (line[0] == '"') {
            int endQuote = line.find('"', 1);
            name = line.substr(1, endQuote - 1);
            index = endQuote + 2;
        }
        else {
            int comma = line.find(',');
            name = line.substr(0, comma);
            index = comma + 1;
        }

        string data;

        data = trim(line.substr(index, line.find(',', index) - index));
        minPlayers = stoi(data);
        index = line.find(',', index) + 1;

        data = trim(line.substr(index, line.find(',', index) - index));
        maxPlayers = stoi(data);
        index = line.find(',', index) + 1;

        data = trim(line.substr(index, line.find(',', index) - index));
        maxPlayTime = stoi(data);
        index = line.find(',', index) + 1;

        data = trim(line.substr(index, line.find(',', index) - index));
        minPlayTime = stoi(data);
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
