#include "comment.h"

Comment::Comment(User* a = 0, QString c = "") : author(a), content(c) {}
User*& Comment::getAuthor() { return author; }
QString& Comment::getContent() { return content; }
