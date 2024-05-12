#ifndef COMMENT_H
#define COMMENT_H

#include "user.h"


class Comment final
{
private:
    User* author;
    QString content;

public:
    Comment(User*, QString);
    User*& getAuthor();
    QString& getContent();

};

#endif // COMMENT_H
