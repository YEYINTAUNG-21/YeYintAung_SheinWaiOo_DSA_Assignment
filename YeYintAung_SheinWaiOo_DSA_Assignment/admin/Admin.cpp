#include "Admin.h"

Admin::Admin() : adminId(""), name("") {
}

Admin::Admin(const string& id, const string& name) : adminId(id), name(name) {
}

string Admin::getId() const {
    return adminId;
}

string Admin::getName() const {
    return name;
}