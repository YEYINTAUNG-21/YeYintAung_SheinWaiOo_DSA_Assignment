#include "Admin.h"

Admin::Admin() {
    adminId = "";
    name = "";
}

Admin::Admin(const string& id, const string& adminName) {
    adminId = id;
    name = adminName;
}

string Admin::getId() const {
    return adminId;
}

string Admin::getName() const {
    return name;
}