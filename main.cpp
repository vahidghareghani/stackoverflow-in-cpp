#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include "logger.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OSss
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
                            Logger::getInstance().log(*loggedInUser);
                        } catch (WrongUsernameOrPasswordException &e) {
                            last_message = e.what();
                        }
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
                            Logger::getInstance().log(*loggedInUser);
                        } catch (UserAlreadyExistsException &e) {
                            last_message = e.what();
                        } catch (EmailAlreadyExistsException &e) {
                            last_message = e.what();
                        }
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

                // calculate number of questions of logged in user
                int number_of_questions = 0;
                for (int l = 0; l < loggedInUser->contents.size(); l++) {
                    if (loggedInUser->contents[l].type == ContentType::QUESTION) {
                        number_of_questions++;
                    }
                }

                cout
                        << "d. delete account\nl. logout\na. ask\ns. see all questions\nm. my questions\nr. edit question\ne. exit\n";
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
                    case 's': { //see all questions and q = number of all questions
                        int q = 1;
                        for (int i = 0; i < User::users.size(); i++) {
                            for (int j = 0; j < User::users[i].contents.size(); j++) {
                                if (User::users[i].contents[j].type == ContentType::QUESTION) {
                                    cout << to_string(q) << ". " << User::users[i].contents[j].body << endl;
                                    q++;
                                }
                            }
                        }
                        cout << "\na. Answer to question\ns. See answers of question\ni. Ignore(Continue)" << endl;
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

                                //make answer content for relationship 1
                                Content ans(answer, ContentType::ANSWER);

                                //Establishing a relationship 1
                                int index = 0, rel = 0;
                                string question;
                                for (int i = 0; i < User::users.size(); i++) {
                                    for (int j = 0; j < User::users[i].contents.size(); j++) {
                                        if (User::users[i].contents[j].type == ContentType::QUESTION && index <= num) {
                                            if (index == num) {
                                                question = User::users[i].contents[j].body;
                                                User::users[i].contents[j].relations.emplace_back(
                                                        ContentRelation(&ans, ContentRelationType::ANSWER_TO));
                                                rel = 1;
                                                break;
                                            } else {
                                                index++;
                                            }
                                        }
                                    }
                                    if (rel) {
                                        break;
                                    }
                                }
                                //Establishing a relationship 2
                                int t = loggedInUser->contents.size();
                                // make question content for relationship 2
                                Content ques(question, ContentType::QUESTION);
                                loggedInUser->contents.emplace_back(ans);
                                loggedInUser->contents[t].relations.emplace_back(
                                        ContentRelation(&ques, ContentRelationType::ANSWER_TO));
                                cout << "The answer was given successfully" << endl;
                                break;
                            }
                            case 's': {
                                int n;
                                while (1) {
                                    cout << "Enter the number of the question that you want to see: ";
                                    cin >> n;
                                    n--;
                                    if (n < q && n >= 0) {
                                        break;
                                    }
                                    cout << "The number that you have entered is not ok, try again!" << endl;
                                }
                                int index = 0;
                                // search and find question then print answers
                                for (int i = 0; i < User::users.size(); i++) {
                                    for (int j = 0; j < User::users[i].contents.size(); j++) {
                                        if (User::users[i].contents[j].type == ContentType::QUESTION && index <= n) {
                                            if (index == n) {
                                                User::users[i].contents[j].visited();
                                                cout << "Question:" << endl;
                                                cout << User::users[i].contents[j].body << endl;
                                                cout << "This question has been visited ";
                                                User::users[i].contents[j].showVisit();
                                                cout    << " time(s)!" << endl;
                                                cout << "Answers:" << endl;
                                                for (int k = 0; k < User::users[i].contents[j].relations.size(); k++) {
                                                    if (User::users[i].contents[j].relations[k].destination->type ==
                                                        ContentType::ANSWER) {
                                                        cout << k + 1 << ". "
                                                             << User::users[i].contents[j].relations[k].destination->body
                                                             << endl;
                                                    }
                                                }
                                                break;
                                            } else {
                                                index++;
                                            }
                                        }
                                    }
                                }
//                                break;



                                cout<<"\n\n\nd. delete your answer\ni. Ignore(Continue)"<<endl;
                                cin>>c;

                                switch (c){
                                    case 'd':

                                        int index=0;
                                        bool hasAnswer=false ;
                                        int q=0;
                                        // search and find question then print answers
                                        for (int i = 0; i < User::users.size(); i++) {
                                            for (int j = 0; j < User::users[i].contents.size(); j++) {
                                                if (User::users[i].contents[j].type == ContentType::QUESTION) {
                                                    if(index==n){
                                                        for (int k = 0; k < User::users[i].contents[j].relations.size(); k++) {
                                                            if (User::users[i].contents[j].relations[k].destination->type == ContentType::ANSWER && User::users[i].username==loggedInUser->username ){
                                                                 hasAnswer= true ;
                                                                cout << k+1 << ". " << User::users[i].contents[j].relations[k].destination->body << endl;
                                                                q++;
                                                            }
                                                        }
                                                    } else{
                                                        index++;
                                                    }
                                                }
                                            }
                                        }
                                        if (hasAnswer==false){
                                            cout<<"you did not answer to this question!!"<<endl;
                                            break;
                                        }


                                        int u;
                                        while (1) {
                                            cout << "Enter the number of answer that you want to delete: ";
                                            cin >> u;
                                            u--;
                                            if (u < q && u >= 0) {
                                                break;
                                            }
                                            cout << "The number that you have entered is not ok, try again!" << endl;
                                        }

                                        index=0;
                                        int indexAswer=0;

                                        for (int i = 0; i < User::users.size(); i++) {
                                            for (int j = 0; j < User::users[i].contents.size(); j++) {
                                                if (User::users[i].contents[j].type == ContentType::QUESTION) {
                                                    if(index==n){
                                                        for (int k = 0; k < User::users[i].contents[j].relations.size(); k++) {
                                                            if (User::users[i].contents[j].relations[k].destination->type == ContentType::ANSWER && User::users[i].username==loggedInUser->username && indexAswer==u ){

                                                                User::users[i].contents[j].relations.erase(User::users[i].contents[j].relations.begin() + indexAswer);
                                                                cout << "answer deleted!" << endl;
                                                                break;

                                                            } else{
                                                                indexAswer++;
                                                            }
                                                        }
                                                    } else{
                                                        index++;
                                                    }
                                                }
                                            }
                                        }



                                }





                            }



                            default:
                                break;
                        }
                        break;
                    }

                    case 'm': { // my questions
                        bool hasQuestion = false;
                        int count = 1;
                        for (int i = 0; i < loggedInUser->contents.size(); ++i) {
                            if (loggedInUser->contents[i].type == ContentType::QUESTION) {
                                hasQuestion = true;
                                cout << to_string(count) << ". " << loggedInUser->contents[i].body << endl;
                                count++;
                            }
                        }
                        if (hasQuestion == false) {
                            cout << "there is no question!!" << endl;
                            break;
                        }

                        cout << "\nd. delete question\ni. Ignore(Continue)" << endl;
                        cin >> c;


                        switch (c) {
                            case 'd': {//first : my questions
                                bool hasQuestion = false;

                                int count = 1;
                                for (int i = 0; i < loggedInUser->contents.size(); ++i) {
                                    if (loggedInUser->contents[i].type == ContentType::QUESTION) {
                                        hasQuestion = true;

                                        cout << to_string(count) << ". " << loggedInUser->contents[i].body << endl;
                                        count++;
                                    }
                                }
                                if (hasQuestion == false) {
                                    cout << "there is no question!!" << endl;
                                    break;
                                }

                                //second : find the index of wanted question
                                int n; //number of question wanted to delete
                                while (1) {
                                    cout << "Enter the number of the question that you want to delete: ";
                                    cin >> n;
                                    n--;
                                    if (n < number_of_questions && n >= 0) {
                                        break;
                                    }
                                    cout << "The number that you have entered is not ok, try again!" << endl;
                                }

                                //third : find the wanted question
                                int index = 0;//index of wanted question
                                for (int i = 0; i < loggedInUser->contents.size(); ++i) {
                                    if (loggedInUser->contents[i].type == ContentType::QUESTION) {
                                        if (index == n) {
                                            loggedInUser->contents.erase(loggedInUser->contents.begin() + index);
                                            cout << "question deleted!" << endl;
                                            break;
                                        } else {
                                            index++;
                                        }
                                    }
                                }
                                break;
                            }
                            case 'i': {
                                break;
                            }


                        }
                        break;
                    }

                    case 'r' : { //edit questions
                        int count = 1;
                        for (int i = 0; i < loggedInUser->contents.size(); ++i) {
                            if (loggedInUser->contents[i].type == ContentType::QUESTION) {
                                cout << to_string(count) << ". " << loggedInUser->contents[i].body << endl;
                                count++;
                            }
                        }
                        int number;
                        while (1) {
                            cout << "Enter the number of the question that you want to edit: ";
                            cin >> number;
                            number--;
                            if (number < number_of_questions && number >= 0) {
                                break;
                            }
                            cout << "The number that you have entered is not ok, try again!" << endl;
                        }
                        string newQues;
                        cout << "Enter the edited question: ";
                        getchar();
                        getline(cin, newQues);
                        loggedInUser->contents[number].body = newQues;
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

