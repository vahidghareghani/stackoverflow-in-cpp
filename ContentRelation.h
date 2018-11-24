#pragma once

enum ContentRelationType {
  DUPLICATE_OF,
  ANSWER_TO
};
class Content;

class ContentRelation {
    Content* destination;
    ContentRelationType type;
};
