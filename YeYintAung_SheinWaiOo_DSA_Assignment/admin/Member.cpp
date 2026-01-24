//#include "Member.h"
//
//Member::Member() {}

//Shein-Tested For Temporary Completion
#include "Member.h"

Member::Member() : memberId(""), memberName("") {
}

Member::Member(const string& memberId, const string& memberName)
    : memberId(memberId), memberName(memberName) {
}

string Member::getId() const {
    return memberId;
}

string Member::getName() const {
    return memberName;
}