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
};
