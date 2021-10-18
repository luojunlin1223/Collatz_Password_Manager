#pragma once
#include "User.h"
class AnonymousUsers :
    public User
{
public:
    AnonymousUsers(string password);
    ~AnonymousUsers();
    void save(const string file_name);
private:
    string password;
};

