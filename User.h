#pragma once

#include <iostream>
#include "AbstractUser.h"
#include "Content.h"

class User : public AbstractUser {
public:
    User(string username, string password, string email, UserType type);
    friend std::ofstream& operator <<(std::ofstream& of, User& user);
    static void init(const string &salt);

public:
    void set_password(string password);
    bool check_password(string password);

public:
    bool authenticate(string username, string password);
    void deleteAccount();

public:
    static User& login(string username, string password);
    static User& signup(string username, string password, string email);

public:
    vector<Content> contents;

public:
    static vector<User> users;

private:
    static string salt;

};

