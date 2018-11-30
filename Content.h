#pragma once

#include <iostream>
#include "Content.h"
#include "ContentRelation.h"
#include <vector>
using namespace std;
enum ContentType{
    QUESTION,
    ANSWER
};

class Content {
private:
    mutable int visits;

public:
    string body;
    ContentType type;
    vector<ContentRelation> relations;
    Content(string body, ContentType type) : body(body), type(type) {
        visits = 0;
    };
    void visited() const {
        visits ++;
    }
    void showVisit() {
        cout << visits;
    }
};

