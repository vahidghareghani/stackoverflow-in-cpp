#include <utility>
#include <sstream>
#include "User.h"
#include "Exceptions.h"
#include <iostream>

std::vector<User> User::users;
std::string User::salt;


User::User(std::string username, string password, string email, UserType type){
    lower(username);
    this->username = username;
    set_password(std::move(password));
    this->type = type;
    this->email = email;
}

void User::set_password(string password){
    size_t ps = pass_hash(password + salt);
    stringstream out;
    out << ps;
    this->password = out.str();
}

bool User::check_password(string password){
    size_t check = pass_hash(password + salt);
    stringstream out;
    out << check;
    return (this->password == out.str());
}

bool User::authenticate(string username, string password){
    lower(username);
    return this->username == username and check_password(password);
}
void User::deleteAccount(){
    if (this->type == UserType::ADMIN) {
        throw DeleteAdminException();
    }

    for (auto user = users.begin(); user != users.end();user++){
        if ( user->username == this->username  ) {
            users.erase(user);
            break;
        }
    }
}

User& User::login(string username, string password){
    for (auto &user : users) {
        if(user.authenticate(username, password)) {
            return user;
        }
    }
    throw WrongUsernameOrPasswordException();
}

User& User::signup(string username, string password, string email){
    for (auto &user : users) {
        if (user.username == username) {
            throw UserAlreadyExistsException();
        } if (user.email == email) {
            throw EmailAlreadyExistsException();
        }
    }
    //Create user
    users.emplace_back(username, password, email, UserType::MEMBER);
    return users[users.size() - 1];
}

void User::init(const string &salt) {
    User::salt = salt;
    users.reserve(20);
    users.emplace_back("admin", "admin", "info@stack.com", UserType::ADMIN);
}
