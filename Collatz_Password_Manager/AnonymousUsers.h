#pragma once
#include "User.h"
class AnonymousUsers :
    public User
{
public:
    AnonymousUsers(string password);
    AnonymousUsers(wstring password);
    ~AnonymousUsers();
    void save(const string file_name,string password);
    void save(const string file_name, wstring password);
private:
    string password;
    wstring wpassword;
};

