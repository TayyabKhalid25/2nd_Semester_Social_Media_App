#ifndef PAGE_H
#define PAGE_H

#include <QString>
#include "user.h"
#include "post.h"

class Page final
{
private:
    int pageID, totalPosts, totalLikes;
    User* owner;
    QString title;
    Post** posts;

public:
    Page(int, User*, QString, int, int);
    ~Page();
    int& getPageID();
    User*& getOwner();
    QString& getTitle();
    int& getTotalPosts();
    Post**& getPosts();
    int& getTotalLikes();

};

#endif // PAGE_H
