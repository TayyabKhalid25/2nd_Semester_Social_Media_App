#ifndef PAGE_H
#define PAGE_H

#include <QString>
#include "user.h"
#include "post.h"

class Page
{
private:
    int pageID;
    User* owner;
    QString title;
    int totalPosts;
    Post** posts;
    int totalLikes;

public:
    Page(int, QString, int, int);
    int& getPageID();
    User*& getOwner();
    QString& getTitle();
    int& getTotalPosts();
    Post**& getPosts();
    int& getTotalLikes();

};

#endif // PAGE_H
