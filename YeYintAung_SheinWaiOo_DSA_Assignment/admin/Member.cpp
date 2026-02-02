#include "Member.h"

Member::Member(){
    memberId = "";
    memberName = "";
}

Member::Member(const string& Id, const string& Name){
    memberId = Id;
    memberName = Name;
}

string Member::getId() const {
    return memberId;
}

string Member::getName() const {
    return memberName;
}

