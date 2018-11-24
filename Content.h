#pragma once

enum ContentType{
  QUESTION,
  ANSWER
};

class Content {
public:
  string body;
  ContentType type;
  int visits;
  vector<ContentRelation> relations;
  Content(string body, ContentType type) : body(body), type(type) {
    visits = 0;
  }
};
