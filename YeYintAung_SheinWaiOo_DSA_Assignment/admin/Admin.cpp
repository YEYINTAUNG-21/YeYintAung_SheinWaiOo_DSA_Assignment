/*
Name: Ye Yint Aung
Group - 3
Student ID - S10268975C
*/
#include "Admin.h"

/*
Function: Admin
Description: Default constructor that initializes an Admin object with empty ID and name.
Parameters:
- None
Returns:
- None
*/
Admin::Admin() {
    adminId = "";
    name = "";
}

/*
Function: Admin
Description: Parameterized constructor that initializes an Admin object with a given ID and name.
Parameters:
- id: The unique identifier for the admin.
- adminName: The name of the admin.
Returns:
- None
*/
Admin::Admin(const string& id, const string& adminName) {
    adminId = id;
    name = adminName;
}

/*
Function: getId
Description: Retrieves the admin's unique identifier.
Parameters:
- None
Returns:
- string: The admin ID.
*/
string Admin::getId() const {
    return adminId;
}

/*
Function: getName
Description: Retrieves the admin's name.
Parameters:
- None
Returns:
- string: The admin name.
*/
string Admin::getName() const {
    return name;
}