#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include "logger.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;


enum MenuState {
    START,
    LOGGED_IN,
    END
};

int main() {
    User::init("SECRET_KEY");
    User *loggedInUser = nullptr;
    MenuState menuState = MenuState::START;
    string last_message;

    char choice, c;
    while (menuState != MenuState::END) {
        system(CLEAR);
        if (!last_message.empty())
            cout << last_message << endl;
        last_message = "";
        switch (menuState) {
            case MenuState::START: {
                cout << "1. login\n2. signup\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case '1': { // login
                        try {
                            string username, password;
                            cout << "Enter Username: ";
                            cin >> username;
                            cout << "Enter Password: ";
                            cin >> password;
                            loggedInUser = &User::login(username, password);
                            menuState = MenuState::LOGGED_IN;
                        } catch (WrongUsernameOrPasswordException &e) {
                            last_message = e.what();
                        }
                        Logger::getInstance().log(*loggedInUser);
                        break;
                    }
                    case '2': { // signup
                        try {
                            string username, password, email;
                            cout << "Enter Username: ";
                            cin >> username;
                            cout << "Enter Password: ";
                            cin >> password;
                            cout << "Enter Email: ";
                            cin >> email;
                            loggedInUser = &User::signup(username, password, email);
                            menuState = MenuState::LOGGED_IN;
                            last_message = "User signed up!";
                        } catch (UserAlreadyExistsException &e) {
                            last_message = e.what();
                        } catch (EmailAlreadyExistsException &e) {
                            last_message = e.what();
                        }
                        Logger::getInstance().log(*loggedInUser);
                        break;
                    }
                    case 'e': { // exit
                        menuState = MenuState::END;
                        break;
                    }
                    default: { // unknown input
                        last_message = "Unknown Input\n";
                        break;
                    }
                }
                break;
            }
            case MenuState::LOGGED_IN: {
                cout << "d. delete account\nl. logout\na. ask\ns. see all questions\nm. my questions\nr. edit question\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case 'd': { //delete account
                        try {
                            loggedInUser->deleteAccount();
                            cout << "Account successfully deleted\n";
                            loggedInUser = nullptr;
                            menuState = MenuState::START;
                        }
                        catch (DeleteAdminException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case 'l': { // logout
                        loggedInUser = nullptr;
                        menuState = MenuState::START;
                        last_message = "GOOD BYE!";
                        break;
                    }
                    case 'a' : { //ask question
                        string ques;
                        getchar();
                        cout << "Enter your question: ";
                        getline(cin, ques);
                        loggedInUser->contents.emplace_back(ques, ContentType::QUESTION);
                        break;
                    }
                    case 's': { //see all questions
                        int q = 1;
                        for (int i = 0; i < User::users.size(); i++) {
                            for (int j = 0; j < User::users[i].contents.size(); j++) {
                                if (User::users[i].contents[j].type == ContentType::QUESTION) {
                                    cout << to_string(q) << ". " << User::users[i].contents[j].body << endl;
                                    q++;
                                }
                            }
                        }
                        cout << "\na. answer to question\ns. see answers of question\ni. ignore" << endl;
                        cin >> c;
                        switch (c) {
                            case 'a': {
                                int num;
                                string answer;

                                //while for to check validation.
                                while (1) {
                                    cout << "Enter the number of the question that you want to answer: ";
                                    cin >> num;
                                    num--;
                                    if (num < q && num >= 0) {
                                        break;
                                    }
                                    cout << "The number that you have entered is not ok, try again!" << endl;
                                }

                                //get answer.
                                cout << "Enter your answer: " << endl;
                                getchar();
                                getline(cin, answer);

                                //make content.
                                Content ans(answer, ContentType::ANSWER);
                                //Establishing a relationship 1
                                int index=1;
                                string question;
                                for (int i = 0; i < User::users.size(); i++) {
                                    for (int j = 0; j < User::users[i].contents.size(); j++) {
                                        if (User::users[i].contents[j].type == ContentType::QUESTION) {
                                            if(index==num){
                                                question = User::users[i].contents[j].body;
                                                User::users[i].contents[j].relations.emplace_back(ContentRelation(&ans, ContentRelationType::ANSWER_TO));
                                            } else{
                                                index++;
                                            }
                                        }
                                    }
                                }
                                //Establishing a relationship 2
                                int t = loggedInUser->contents.size();
                                Content ques(question, ContentType::QUESTION);
                                loggedInUser->contents.emplace_back(ans);
                                loggedInUser->contents[t-1].relations.emplace_back(ContentRelation(&ques, ContentRelationType::ANSWER_TO));
                                cout << "The answer was given successfully" << endl;
                                break;
                            }
                            case 's': {
                                int n;
                                while (1) {
                                    cout << "Enter the number of the question that you want to see: ";
                                    cin >> n;
                                    n--;
                                    if (n < loggedInUser->contents.size() && n >= 0) {
                                        break;
                                    }
                                    cout << "The number that you have entered is not ok, try again!" << endl;
                                }
                                int index=1;
                                for (int i = 0; i < User::users.size(); i++) {
                                    for (int j = 0; j < User::users[i].contents.size(); j++) {
                                        if (User::users[i].contents[j].type == ContentType::QUESTION) {
                                            if(index==n){
                                                for (int k = 0; k < User::users[i].contents[j].relations.size(); k++) {
                                                    if (User::users[i].contents[j].relations[k].destination->type == ContentType::ANSWER){
                                                        cout << k+1 << User::users[i].contents[j].relations[k].destination->body << endl;
                                                    }
                                                }
                                            } else{
                                                index++;
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    case 'm':{ // my questions
                        int count = 1;
                        for (int i = 0; i <loggedInUser->contents.size() ; ++i) {
                            if (loggedInUser->contents[i].type == ContentType::QUESTION){
                                cout << to_string(count) << ". " <<loggedInUser->contents[i].body<<endl;
                                count++;
                            }
                        }
                        break;
                    }
                    case 'r' :{ //edit questions
                        int count = 1;
                        for (int i = 0; i < loggedInUser -> contents.size(); ++i) {
                            if (loggedInUser -> contents[i].type == ContentType::QUESTION){
                                cout << to_string(count) << ". " <<loggedInUser->contents[i].body<<endl;
                                count++;
                            }
                        }
                        int number;
                        while (1) {
                            cout << "Enter the number of the question that you want to edit: ";
                            cin >> number;
                            number--;
                            if (number < loggedInUser -> contents.size() && number >= 0) {
                                break;
                            }
                            cout << "The number that you have entered is not ok, try again!" << endl;
                        }
                        string newQues;
                        cout << "Enter the edited question: ";
                        getchar();
                        getline(cin, newQues);
                        loggedInUser -> contents[number].body = newQues;
                        cout << "Question successfully updated!" << endl;
                        break;
                    }
                    case 'e': { // exit
                        menuState = MenuState::END;
                        break;
                    }
                    default: { // unknown input
                        last_message = "Unknown Input\n";
                        break;
                    }

                }
            }
        }
    }
    system(CLEAR);
    cout << "GOODBYE" << endl;
    return 0;
}

