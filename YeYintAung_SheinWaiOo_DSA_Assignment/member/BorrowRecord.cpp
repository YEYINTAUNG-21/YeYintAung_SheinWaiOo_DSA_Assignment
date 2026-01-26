#include "BorrowRecord.h"

BorrowRecord::BorrowRecord() : memberId(""), gameName(""), returned(false) {
}

BorrowRecord::BorrowRecord(const std::string& memberId, const std::string& gameName)
    : memberId(memberId), gameName(gameName), returned(false) {
}

std::string BorrowRecord::getMemberId() const {
    return memberId;
}

std::string BorrowRecord::getGameName() const {
    return gameName;
}

bool BorrowRecord::isReturned() const {
    return returned;
}

void BorrowRecord::markReturned() {
    returned = true;
}