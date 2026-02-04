#pragma once
#include<string>
#include<iostream>
#include "../admin/GameList.h"
#include "../admin/MemberList.h"
#include "../member/borrowList.h"
#include "../member/RatingList.h"

using namespace std;

class CSVReader
{
private:

public:
	static void loadGame(const string& filename, GameList& gameList);
	static void loadMember(const string& filename, MemberList& memberList);
	static void loadBorrow(const std::string& filename, BorrowList& borrowList, const MemberList& memberList, const GameList& gameList);
	static void loadReview(const string& filename, RatingList& ratingList);
};