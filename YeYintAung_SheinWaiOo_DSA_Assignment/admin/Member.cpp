/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#include "Member.h"

/*
Function: Member
Description: Default constructor that initializes a member with empty ID and name.
Parameters:
- None
Returns:
- None
*/
Member::Member(){
    memberId = "";
    memberName = "";
}

/*
Function: Member
Description: Parameterized constructor that initializes a member with a given ID and name.
Parameters:
- Id: The unique identifier for the member.
- Name: The name of the member.
Returns:
- None
*/
Member::Member(const string& Id, const string& Name){
    memberId = Id;
    memberName = Name;
}

/*
Function: getId
Description: Retrieves the member's unique identifier.
Parameters:
- None
Returns:
- string: The member ID.
*/
string Member::getId() const {
    return memberId;
}

/*
Function: getName
Description: Retrieves the member's name.
Parameters:
- None
Returns:
- string: The member name.
*/
string Member::getName() const {
    return memberName;
}

