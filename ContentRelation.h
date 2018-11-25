#pragma once

enum ContentRelationType {
    DUPLICATE_OF,
    ANSWER_TO
};
class Content;

class ContentRelation {
public:
    ContentRelation(Content* destination, ContentRelationType type):type(type), destination(destination) {};
    Content* destination;
    ContentRelationType type;
};

