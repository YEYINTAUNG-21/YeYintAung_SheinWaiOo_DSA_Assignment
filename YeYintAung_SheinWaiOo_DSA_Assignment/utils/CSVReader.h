#pragma once
#include<string>
#include<iostream>
#include "../admin/GameList.h"
using namespace std;

class CSVReader
{
private:

public:
	static void loadGame(const string& filename, GameList& gameList);
};